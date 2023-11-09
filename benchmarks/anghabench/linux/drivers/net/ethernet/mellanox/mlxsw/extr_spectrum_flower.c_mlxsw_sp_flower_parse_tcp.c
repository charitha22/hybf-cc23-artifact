#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct mlxsw_sp_acl_rule_info {int dummy; } ;
struct mlxsw_sp {TYPE_2__* bus_info; } ;
struct flow_rule {int dummy; } ;
struct flow_match_tcp {TYPE_4__* mask; TYPE_3__* key; } ;
struct TYPE_5__ {int /*<<< orphan*/  extack; } ;
struct flow_cls_offload {TYPE_1__ common; } ;
struct TYPE_8__ {int flags; } ;
struct TYPE_7__ {int flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_TCP ; 
 scalar_t__ IPPROTO_TCP ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_TCP_FLAGS ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct flow_rule* flow_cls_offload_flow_rule (struct flow_cls_offload*) ; 
 int /*<<< orphan*/  flow_rule_match_key (struct flow_rule const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_rule_match_tcp (struct flow_rule const*,struct flow_match_tcp*) ; 
 int htons (int) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_rulei_keymask_u32 (struct mlxsw_sp_acl_rule_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int) ; 

__attribute__((used)) static int mlxsw_sp_flower_parse_tcp(struct mlxsw_sp *mlxsw_sp,
				     struct mlxsw_sp_acl_rule_info *rulei,
				     struct flow_cls_offload *f,
				     u8 ip_proto)
{
	const struct flow_rule *rule = flow_cls_offload_flow_rule(f);
	struct flow_match_tcp match;

	if (!flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_TCP))
		return 0;

	if (ip_proto != IPPROTO_TCP) {
		NL_SET_ERR_MSG_MOD(f->common.extack, "TCP keys supported only for TCP");
		dev_err(mlxsw_sp->bus_info->dev, "TCP keys supported only for TCP\n");
		return -EINVAL;
	}

	flow_rule_match_tcp(rule, &match);

	if (match.mask->flags & htons(0x0E00)) {
		NL_SET_ERR_MSG_MOD(f->common.extack, "TCP flags match not supported on reserved bits");
		dev_err(mlxsw_sp->bus_info->dev, "TCP flags match not supported on reserved bits\n");
		return -EINVAL;
	}

	mlxsw_sp_acl_rulei_keymask_u32(rulei, MLXSW_AFK_ELEMENT_TCP_FLAGS,
				       ntohs(match.key->flags),
				       ntohs(match.mask->flags));
	return 0;
}