#ifndef IK_SOLVER_H
#define IK_SOLVER_H

#include "ik/config.h"
#include "ik/ordered_vector.h"
#include "ik/vec3.h"
#include "ik/quat.h"

C_HEADER_BEGIN

struct ik_effector_t;
struct ik_node_t;
struct ik_solver_t;

typedef void (*ik_solver_destroy_func)(struct ik_solver_t*);
typedef int (*ik_solver_rebuild_data_func)(struct ik_solver_t*);
typedef void (*ik_solver_recalculate_segment_lengths_func)(struct ik_solver_t*);
typedef int (*ik_solver_solve_func)(struct ik_solver_t*);

typedef void (*ik_solver_apply_constraint_cb_func)(struct ik_node_t*);
typedef void (*ik_solver_apply_result_cb_func)(struct ik_node_t*);

enum solver_algorithm_e
{
    SOLVER_FABRIK
    /* TODO Not implemented
    SOLVER_JACOBIAN_INVERSE,
    SOLVER_JACOBIAN_TRANSPOSE */
};

enum solver_flags_e
{
    /*!
     * @brief Causes the root node in the tree to be excluded from the list of
     * nodes to solve for. It won't be affected by the solver, but it may still
     * be passed through to the result callback function.
     */
    SOLVER_EXCLUDE_ROOT                   = 0x01,

    /*!
     * @brief This is a post-processing step which can optionally be enabled.
     * Causes the correct global angles to be calculated for each node in the
     * solved tree. The results can be retrieved from node->solved_rotation.
     * This should definitely be enabled for skinned models.
     */
    SOLVER_CALCULATE_FINAL_ROTATIONS      = 0x02,

    /* (not yet implemented)
     * Calculate node angles for each iteration, which may be useful in the
     * solver->apply_constraint callback function.
     */
    SOLVER_CALCULATE_CONSTRAINT_ROTATIONS = 0x04,

    SOLVER_CALCULATE_TARGET_ROTATIONS     = 0x08,

    /*!
     * @brief The solver will not reset the solved data to its initial state
     * before solving. The result is a more "continuous" or "ongoing" solution
     * to the tree, because it will use the previous solved tree as a bases for
     * solving the next tree.
     */
    SOLVER_SKIP_RESET                     = 0x10,

    /*!
     * @brief The solver will not call the solver->apply_result callback
     * function after solving. The results are still calculated. This is useful
     * if you wish to delay the point at which the solved data is applied. You
     * can later call ik_solver_iterate_tree() to initiate calls to the
     * callback function.
     */
    SOLVER_SKIP_APPLY                     = 0x20
};

/*!
 * @brief This is a base struct for all solvers.
 */
#define SOLVER_DATA_HEAD                                             \
    ik_solver_apply_constraint_cb_func apply_constraint;             \
    ik_solver_apply_result_cb_func     apply_result;                 \
                                                                     \
    int32_t                            max_iterations;               \
    float                              tolerance;                    \
    uint8_t                            flags;                        \
                                                                     \
    /* Derived structure callbacks */                                \
    ik_solver_destroy_func             destroy;                      \
    ik_solver_rebuild_data_func        rebuild_data;                 \
    ik_solver_recalculate_segment_lengths_func recalculate_segment_lengths; \
    ik_solver_solve_func               solve;                        \
                                                                     \
    struct ordered_vector_t            effector_nodes_list;          \
    struct ik_node_t*                  tree;
struct ik_solver_t
{
    SOLVER_DATA_HEAD
};

/*!
 * @brief Allocates a new solver object according to the specified algorithm.
 *
 * Once the solver is created, you can configure the solver to enable/disable
 * various features depending on your needs.
 *
 * The following attributes can be changed at any point.
 *  + solver->apply_result
 *       This is the main mechanism with which to obtain the solved data.
 *       Assign a callback function here and it will be called for every node
 *       in the tree when a new target position/rotation has been calculated.
 *       You can use the node->user_data attribute to store external node
 *       specific data, which can be accessed again the in callback function.
 *  + solver->max_iterations
 *       Specifies the maximum number of iterations. The more iterations, the
 *       more exact the result will be. The default value for the FABRIK solver
 *       is 20, but you can get away with values as low as 5.
 *  + solver->tolerance
 *       This value can be changed at any point. Specifies the acceptable
 *       distance each effector needs to be to its target position. The solver
 *       will stop iterating if the effectors are within this distance. The
 *       default value is 1e-3. Recommended values are 100th of your world
 *       unit.
 *  + solver->flags
 *       Changes the behaviour of the solver. See the enum solver_flags_e for
 *       more information.
 *
 * The following attributes can be accessed (read from) but should not be
 * modified.
 *  + solver->tree
 *       The tree to be solved. You may modify the nodes in the tree.
 *       @note If you add/remove nodes or if you add/remove effectors, you
 *       must call ik_solver_rebuild_data() so the internal solver structures
 *       are updated. Failing to do so may cause segfaults. If you're just
 *       updating positions/rotations or any of the other public data then
 *       there is no need to rebuild data.
 *  + solver->effector_nodes_list
 *       A vector containing pointers to nodes in the tree which have an
 *       effector attached to them. You may not modify this list, but you may
 *       iterate it.
 * @param[in] algorithm The algorithm to use. Currently, only FABRIK is
 * supported.
 */
IK_PUBLIC_API struct ik_solver_t*
ik_solver_create(enum solver_algorithm_e algorithm);

/*!
 * @brief Destroys the solver and all nodes/effectors that are part of the
 * solver. Any pointers to tree nodes are invalid after this function returns.
 */
IK_PUBLIC_API void
ik_solver_destroy(struct ik_solver_t* solver);

/*!
 * @brief Sets the tree to solve. The solver takes ownership of the tree, so
 * destroying the solver will destroy all nodes in the tree. Note that you will
 * have to call ik_solver_rebuild_data() before being able to solve it. If the
 * solver already has a tree, then said tree will be destroyed.
 */
IK_PUBLIC_API void
ik_solver_set_tree(struct ik_solver_t* solver, struct ik_node_t* root);

/*!
 * @brief The solver releases any references to a previously set tree and
 * returns the root node of said tree. Any proceeding calls that involve the
 * tree (e.g. solve or rebuild) will have no effect until a new tree is set.
 * @return If the solver has no tree then NULL is returned.
 */
IK_PUBLIC_API struct ik_node_t*
ik_solver_unlink_tree(struct ik_solver_t* solver);

/*!
 * @brief The solver releases any references to a previously set tree and
 * destroys it.
 */
IK_PUBLIC_API void
ik_solver_destroy_tree(struct ik_solver_t* solver);

/*!
 * @brief Causes the set tree to be processed into more optimal data structures
 * for solving. Must be called before ik_solver_solve().
 * @note Needs to be called whenever the tree changes in any way. I.e. if you
 * remove nodes or add nodes, or if you remove effectors or add effectors,
 * you must call this again before calling the solver.
 */
IK_PUBLIC_API int
ik_solver_rebuild_data(struct ik_solver_t* solver);

/*!
 * @brief Unusual, but if you have a tree with translational motions such that
 * the distances between nodes changes (perhaps a slider?), you can call this
 * to re-calculate the segment lengths after assigning new positions to the
 * nodes.
 * @note This function gets called by ik_solver_rebuild_data().
 */
IK_PUBLIC_API void
ik_solver_recalculate_segment_lengths(struct ik_solver_t* solver);

/*!
 * @brief Solves the IK problem. The node solutions will be provided via a
 * callback function, which can be registered to the solver by assigning it to
 * solver->apply_result.
 */
IK_PUBLIC_API int
ik_solver_solve(struct ik_solver_t* solver);

/*!
 * @brief Iterates all nodes in the internal tree, breadth first, and calls the
 * solver->apply_result callback function for every node.
 *
 * This gets called automatically for you by ik_solver_solve() if
 * SOLVER_SKIP_APPLY is **not** set. This function could also be used to reset
 * your own scene graph to its initial state by reading the node->position and
 * node->rotation properties.
 */
IK_PUBLIC_API void
ik_solver_iterate_tree(struct ik_solver_t* solver);

/*!
 * @brief Sets the solved positions and rotations equal to the original
 * positions and rotations for every node in the tree. The solver will call
 * this automatically if SOLVER_SKIP_RESET is **not** set.
 */
IK_PUBLIC_API void
ik_solver_reset_solved_data(struct ik_solver_t* solver);

C_HEADER_END

#endif /* IK_SOLVER_H */
