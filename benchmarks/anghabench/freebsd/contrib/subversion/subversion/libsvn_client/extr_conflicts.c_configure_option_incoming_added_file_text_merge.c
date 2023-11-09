#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_wc_operation_t ;
typedef  scalar_t__ svn_wc_conflict_reason_t ;
typedef  scalar_t__ svn_wc_conflict_action_t ;
typedef  char const* svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
struct TYPE_12__ {int /*<<< orphan*/  local_abspath; } ;
typedef  TYPE_2__ svn_client_conflict_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_resolution_option (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 char* apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  resolve_merge_incoming_added_file_text_merge ; 
 int /*<<< orphan*/  resolve_merge_incoming_added_file_text_update ; 
 scalar_t__ svn_client_conflict_get_incoming_change (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_client_conflict_get_incoming_new_repos_location (char const**,char const**,scalar_t__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_client_conflict_get_local_change (TYPE_2__*) ; 
 scalar_t__ svn_client_conflict_get_operation (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_client_conflict_option_incoming_added_file_text_merge ; 
 scalar_t__ svn_client_conflict_tree_get_victim_node_kind (TYPE_2__*) ; 
 char const* svn_dirent_local_style (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_skip_ancestor (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_wc__get_wcroot (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_conflict_action_add ; 
 scalar_t__ svn_wc_conflict_reason_added ; 
 scalar_t__ svn_wc_conflict_reason_obstructed ; 
 scalar_t__ svn_wc_operation_merge ; 

__attribute__((used)) static svn_error_t *
configure_option_incoming_added_file_text_merge(svn_client_conflict_t *conflict,
                                                svn_client_ctx_t *ctx,
                                                apr_array_header_t *options,
                                                apr_pool_t *scratch_pool)
{
  svn_wc_operation_t operation;
  svn_wc_conflict_action_t incoming_change;
  svn_wc_conflict_reason_t local_change;
  svn_node_kind_t victim_node_kind;
  const char *incoming_new_repos_relpath;
  svn_revnum_t incoming_new_pegrev;
  svn_node_kind_t incoming_new_kind;

  operation = svn_client_conflict_get_operation(conflict);
  incoming_change = svn_client_conflict_get_incoming_change(conflict);
  local_change = svn_client_conflict_get_local_change(conflict);
  victim_node_kind = svn_client_conflict_tree_get_victim_node_kind(conflict);
  SVN_ERR(svn_client_conflict_get_incoming_new_repos_location(
            &incoming_new_repos_relpath, &incoming_new_pegrev,
            &incoming_new_kind, conflict, scratch_pool,
            scratch_pool));

  if (victim_node_kind == svn_node_file &&
      incoming_new_kind == svn_node_file &&
      incoming_change == svn_wc_conflict_action_add &&
      (local_change == svn_wc_conflict_reason_obstructed ||
       local_change == svn_wc_conflict_reason_added))
    {
      const char *description;
      const char *wcroot_abspath;

      SVN_ERR(svn_wc__get_wcroot(&wcroot_abspath, ctx->wc_ctx,
                                 conflict->local_abspath, scratch_pool,
                                 scratch_pool));

      if (operation == svn_wc_operation_merge)
        description =
          apr_psprintf(scratch_pool, _("merge '^/%s@%ld' into '%s'"),
            incoming_new_repos_relpath, incoming_new_pegrev,
            svn_dirent_local_style(
              svn_dirent_skip_ancestor(wcroot_abspath,
                                       conflict->local_abspath),
              scratch_pool));
      else
        description =
          apr_psprintf(scratch_pool, _("merge local '%s' and '^/%s@%ld'"),
            svn_dirent_local_style(
              svn_dirent_skip_ancestor(wcroot_abspath,
                                       conflict->local_abspath),
              scratch_pool),
            incoming_new_repos_relpath, incoming_new_pegrev);

      add_resolution_option(
        options, conflict,
        svn_client_conflict_option_incoming_added_file_text_merge,
        _("Merge the files"), description,
        operation == svn_wc_operation_merge
          ? resolve_merge_incoming_added_file_text_merge
          : resolve_merge_incoming_added_file_text_update);
    }

  return SVN_NO_ERROR;
}