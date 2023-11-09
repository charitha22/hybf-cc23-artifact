#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_unblock_ctl {int requeue; int /*<<< orphan*/  unblock_action; } ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_lock_res {int l_flags; int l_blocking; int l_level; int /*<<< orphan*/  l_lock; TYPE_1__* l_ops; int /*<<< orphan*/  l_name; scalar_t__ l_ex_holders; scalar_t__ l_ro_holders; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  (* set_lvb ) (struct ocfs2_lock_res*) ;int /*<<< orphan*/  (* downconvert_worker ) (struct ocfs2_lock_res*,int) ;int /*<<< orphan*/  (* check_downconvert ) (struct ocfs2_lock_res*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DLM_LOCK_EX ; 
 int DLM_LOCK_NL ; 
 int DLM_LOCK_PR ; 
 int LOCK_TYPE_REQUIRES_REFRESH ; 
 int LOCK_TYPE_USES_LVB ; 
 int /*<<< orphan*/  ML_BASTS ; 
 int OCFS2_LOCK_BLOCKED ; 
 int OCFS2_LOCK_BUSY ; 
 int OCFS2_LOCK_NEEDS_REFRESH ; 
 int OCFS2_LOCK_PENDING ; 
 int OCFS2_LOCK_REFRESHING ; 
 int OCFS2_LOCK_UPCONVERT_FINISHING ; 
 int /*<<< orphan*/  UNBLOCK_STOP_POST ; 
 int /*<<< orphan*/  lockres_clear_flags (struct ocfs2_lock_res*,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_cancel_convert (struct ocfs2_super*,struct ocfs2_lock_res*) ; 
 int ocfs2_downconvert_lock (struct ocfs2_super*,struct ocfs2_lock_res*,int,int,unsigned int) ; 
 int ocfs2_highest_compat_lock_level (int) ; 
 int ocfs2_prepare_cancel_convert (struct ocfs2_super*,struct ocfs2_lock_res*) ; 
 unsigned int ocfs2_prepare_downconvert (struct ocfs2_lock_res*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ocfs2_lock_res*,int) ; 
 int /*<<< orphan*/  stub2 (struct ocfs2_lock_res*,int) ; 
 int /*<<< orphan*/  stub3 (struct ocfs2_lock_res*) ; 

__attribute__((used)) static int ocfs2_unblock_lock(struct ocfs2_super *osb,
			      struct ocfs2_lock_res *lockres,
			      struct ocfs2_unblock_ctl *ctl)
{
	unsigned long flags;
	int blocking;
	int new_level;
	int level;
	int ret = 0;
	int set_lvb = 0;
	unsigned int gen;

	spin_lock_irqsave(&lockres->l_lock, flags);

recheck:
	/*
	 * Is it still blocking? If not, we have no more work to do.
	 */
	if (!(lockres->l_flags & OCFS2_LOCK_BLOCKED)) {
		BUG_ON(lockres->l_blocking != DLM_LOCK_NL);
		spin_unlock_irqrestore(&lockres->l_lock, flags);
		ret = 0;
		goto leave;
	}

	if (lockres->l_flags & OCFS2_LOCK_BUSY) {
		/* XXX
		 * This is a *big* race.  The OCFS2_LOCK_PENDING flag
		 * exists entirely for one reason - another thread has set
		 * OCFS2_LOCK_BUSY, but has *NOT* yet called dlm_lock().
		 *
		 * If we do ocfs2_cancel_convert() before the other thread
		 * calls dlm_lock(), our cancel will do nothing.  We will
		 * get no ast, and we will have no way of knowing the
		 * cancel failed.  Meanwhile, the other thread will call
		 * into dlm_lock() and wait...forever.
		 *
		 * Why forever?  Because another node has asked for the
		 * lock first; that's why we're here in unblock_lock().
		 *
		 * The solution is OCFS2_LOCK_PENDING.  When PENDING is
		 * set, we just requeue the unblock.  Only when the other
		 * thread has called dlm_lock() and cleared PENDING will
		 * we then cancel their request.
		 *
		 * All callers of dlm_lock() must set OCFS2_DLM_PENDING
		 * at the same time they set OCFS2_DLM_BUSY.  They must
		 * clear OCFS2_DLM_PENDING after dlm_lock() returns.
		 */
		if (lockres->l_flags & OCFS2_LOCK_PENDING) {
			mlog(ML_BASTS, "lockres %s, ReQ: Pending\n",
			     lockres->l_name);
			goto leave_requeue;
		}

		ctl->requeue = 1;
		ret = ocfs2_prepare_cancel_convert(osb, lockres);
		spin_unlock_irqrestore(&lockres->l_lock, flags);
		if (ret) {
			ret = ocfs2_cancel_convert(osb, lockres);
			if (ret < 0)
				mlog_errno(ret);
		}
		goto leave;
	}

	/*
	 * This prevents livelocks. OCFS2_LOCK_UPCONVERT_FINISHING flag is
	 * set when the ast is received for an upconvert just before the
	 * OCFS2_LOCK_BUSY flag is cleared. Now if the fs received a bast
	 * on the heels of the ast, we want to delay the downconvert just
	 * enough to allow the up requestor to do its task. Because this
	 * lock is in the blocked queue, the lock will be downconverted
	 * as soon as the requestor is done with the lock.
	 */
	if (lockres->l_flags & OCFS2_LOCK_UPCONVERT_FINISHING)
		goto leave_requeue;

	/*
	 * How can we block and yet be at NL?  We were trying to upconvert
	 * from NL and got canceled.  The code comes back here, and now
	 * we notice and clear BLOCKING.
	 */
	if (lockres->l_level == DLM_LOCK_NL) {
		BUG_ON(lockres->l_ex_holders || lockres->l_ro_holders);
		mlog(ML_BASTS, "lockres %s, Aborting dc\n", lockres->l_name);
		lockres->l_blocking = DLM_LOCK_NL;
		lockres_clear_flags(lockres, OCFS2_LOCK_BLOCKED);
		spin_unlock_irqrestore(&lockres->l_lock, flags);
		goto leave;
	}

	/* if we're blocking an exclusive and we have *any* holders,
	 * then requeue. */
	if ((lockres->l_blocking == DLM_LOCK_EX)
	    && (lockres->l_ex_holders || lockres->l_ro_holders)) {
		mlog(ML_BASTS, "lockres %s, ReQ: EX/PR Holders %u,%u\n",
		     lockres->l_name, lockres->l_ex_holders,
		     lockres->l_ro_holders);
		goto leave_requeue;
	}

	/* If it's a PR we're blocking, then only
	 * requeue if we've got any EX holders */
	if (lockres->l_blocking == DLM_LOCK_PR &&
	    lockres->l_ex_holders) {
		mlog(ML_BASTS, "lockres %s, ReQ: EX Holders %u\n",
		     lockres->l_name, lockres->l_ex_holders);
		goto leave_requeue;
	}

	/*
	 * Can we get a lock in this state if the holder counts are
	 * zero? The meta data unblock code used to check this.
	 */
	if ((lockres->l_ops->flags & LOCK_TYPE_REQUIRES_REFRESH)
	    && (lockres->l_flags & OCFS2_LOCK_REFRESHING)) {
		mlog(ML_BASTS, "lockres %s, ReQ: Lock Refreshing\n",
		     lockres->l_name);
		goto leave_requeue;
	}

	new_level = ocfs2_highest_compat_lock_level(lockres->l_blocking);

	if (lockres->l_ops->check_downconvert
	    && !lockres->l_ops->check_downconvert(lockres, new_level)) {
		mlog(ML_BASTS, "lockres %s, ReQ: Checkpointing\n",
		     lockres->l_name);
		goto leave_requeue;
	}

	/* If we get here, then we know that there are no more
	 * incompatible holders (and anyone asking for an incompatible
	 * lock is blocked). We can now downconvert the lock */
	if (!lockres->l_ops->downconvert_worker)
		goto downconvert;

	/* Some lockres types want to do a bit of work before
	 * downconverting a lock. Allow that here. The worker function
	 * may sleep, so we save off a copy of what we're blocking as
	 * it may change while we're not holding the spin lock. */
	blocking = lockres->l_blocking;
	level = lockres->l_level;
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	ctl->unblock_action = lockres->l_ops->downconvert_worker(lockres, blocking);

	if (ctl->unblock_action == UNBLOCK_STOP_POST) {
		mlog(ML_BASTS, "lockres %s, UNBLOCK_STOP_POST\n",
		     lockres->l_name);
		goto leave;
	}

	spin_lock_irqsave(&lockres->l_lock, flags);
	if ((blocking != lockres->l_blocking) || (level != lockres->l_level)) {
		/* If this changed underneath us, then we can't drop
		 * it just yet. */
		mlog(ML_BASTS, "lockres %s, block=%d:%d, level=%d:%d, "
		     "Recheck\n", lockres->l_name, blocking,
		     lockres->l_blocking, level, lockres->l_level);
		goto recheck;
	}

downconvert:
	ctl->requeue = 0;

	if (lockres->l_ops->flags & LOCK_TYPE_USES_LVB) {
		if (lockres->l_level == DLM_LOCK_EX)
			set_lvb = 1;

		/*
		 * We only set the lvb if the lock has been fully
		 * refreshed - otherwise we risk setting stale
		 * data. Otherwise, there's no need to actually clear
		 * out the lvb here as it's value is still valid.
		 */
		if (set_lvb && !(lockres->l_flags & OCFS2_LOCK_NEEDS_REFRESH))
			lockres->l_ops->set_lvb(lockres);
	}

	gen = ocfs2_prepare_downconvert(lockres, new_level);
	spin_unlock_irqrestore(&lockres->l_lock, flags);
	ret = ocfs2_downconvert_lock(osb, lockres, new_level, set_lvb,
				     gen);

leave:
	if (ret)
		mlog_errno(ret);
	return ret;

leave_requeue:
	spin_unlock_irqrestore(&lockres->l_lock, flags);
	ctl->requeue = 1;

	return 0;
}