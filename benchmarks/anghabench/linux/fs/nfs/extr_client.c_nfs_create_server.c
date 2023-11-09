#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nfs_subversion {TYPE_3__* rpc_ops; } ;
struct TYPE_10__ {scalar_t__ minor; scalar_t__ major; } ;
struct nfs_server {scalar_t__ namelen; int /*<<< orphan*/  mount_time; TYPE_5__ fsid; int /*<<< orphan*/  caps; TYPE_2__* nfs_client; int /*<<< orphan*/  cred; } ;
struct nfs_mount_info {int /*<<< orphan*/  mntfh; TYPE_4__* parsed; } ;
struct nfs_fattr {int valid; int /*<<< orphan*/  fsid; } ;
struct TYPE_9__ {int flags; } ;
struct TYPE_8__ {int (* getattr ) (struct nfs_server*,int /*<<< orphan*/ ,struct nfs_fattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {TYPE_1__* rpc_ops; } ;
struct TYPE_6__ {int version; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct nfs_server* ERR_PTR (int) ; 
 scalar_t__ NFS2_MAXNAMLEN ; 
 scalar_t__ NFS3_MAXNAMLEN ; 
 int NFS_ATTR_FATTR ; 
 int /*<<< orphan*/  NFS_CAP_READDIRPLUS ; 
 int NFS_MOUNT_NORDIRPLUS ; 
 int /*<<< orphan*/  current_cred () ; 
 int /*<<< orphan*/  dprintk (char*,unsigned long long,...) ; 
 int /*<<< orphan*/  get_cred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memcpy (TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 struct nfs_fattr* nfs_alloc_fattr () ; 
 struct nfs_server* nfs_alloc_server () ; 
 int /*<<< orphan*/  nfs_free_fattr (struct nfs_fattr*) ; 
 int /*<<< orphan*/  nfs_free_server (struct nfs_server*) ; 
 int nfs_init_server (struct nfs_server*,TYPE_4__*,struct nfs_subversion*) ; 
 int nfs_probe_fsinfo (struct nfs_server*,int /*<<< orphan*/ ,struct nfs_fattr*) ; 
 int /*<<< orphan*/  nfs_server_insert_lists (struct nfs_server*) ; 
 int stub1 (struct nfs_server*,int /*<<< orphan*/ ,struct nfs_fattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct nfs_server *nfs_create_server(struct nfs_mount_info *mount_info,
				     struct nfs_subversion *nfs_mod)
{
	struct nfs_server *server;
	struct nfs_fattr *fattr;
	int error;

	server = nfs_alloc_server();
	if (!server)
		return ERR_PTR(-ENOMEM);

	server->cred = get_cred(current_cred());

	error = -ENOMEM;
	fattr = nfs_alloc_fattr();
	if (fattr == NULL)
		goto error;

	/* Get a client representation */
	error = nfs_init_server(server, mount_info->parsed, nfs_mod);
	if (error < 0)
		goto error;

	/* Probe the root fh to retrieve its FSID */
	error = nfs_probe_fsinfo(server, mount_info->mntfh, fattr);
	if (error < 0)
		goto error;
	if (server->nfs_client->rpc_ops->version == 3) {
		if (server->namelen == 0 || server->namelen > NFS3_MAXNAMLEN)
			server->namelen = NFS3_MAXNAMLEN;
		if (!(mount_info->parsed->flags & NFS_MOUNT_NORDIRPLUS))
			server->caps |= NFS_CAP_READDIRPLUS;
	} else {
		if (server->namelen == 0 || server->namelen > NFS2_MAXNAMLEN)
			server->namelen = NFS2_MAXNAMLEN;
	}

	if (!(fattr->valid & NFS_ATTR_FATTR)) {
		error = nfs_mod->rpc_ops->getattr(server, mount_info->mntfh,
				fattr, NULL, NULL);
		if (error < 0) {
			dprintk("nfs_create_server: getattr error = %d\n", -error);
			goto error;
		}
	}
	memcpy(&server->fsid, &fattr->fsid, sizeof(server->fsid));

	dprintk("Server FSID: %llx:%llx\n",
		(unsigned long long) server->fsid.major,
		(unsigned long long) server->fsid.minor);

	nfs_server_insert_lists(server);
	server->mount_time = jiffies;
	nfs_free_fattr(fattr);
	return server;

error:
	nfs_free_fattr(fattr);
	nfs_free_server(server);
	return ERR_PTR(error);
}