/*!
 * Copyright 2014 by Contributors
 * \file param.h
 * \brief training parameters, statistics used to support tree construction.
 * \author Tianqi Chen
 */
#ifndef XGBOOST_TREE_PARAM_H_
#define XGBOOST_TREE_PARAM_H_

#include <dmlc/parameter.h>
#include <xgboost/data.h>
#include <cmath>
#include <cstring>
#include <limits>
#include <vector>
#include <string>

namespace xgboost {
namespace tree {

/*! \brief training parameters for regression tree */
struct TrainParam : public dmlc::Parameter<TrainParam> {
//TODO: we can define the param that we want to use in the task split here
// 1. first, we define the param as a data member of this TrainParam class
// 2. we then set the bounds and default value of this param

  
  int xgboost_task_gain_output_flag;

  // used to indicated we only conduct the task split N layers before the last layer
  // for example, if the max_depth si set to 5, then we have layer 0 for root, and layer 1,2,3,4 for inner nodes
  // and layer 5 for leaves
  // if conduct_task_split_N_layer_before=0, then we can conduct task split at layer 0,1,2,3,4
  // if conduct_task_split_N_layer_before=1, then we can conduct task split at layer 0,1,2,3 but not 4
  int conduct_task_split_N_layer_before;

  // flag to indicate which kind of leaf output we will use
  int leaf_output_flag;

  // flag to indicate whether output the task gain of the each tree.
  int task_gain_output_flag;

  // file string
  std::string output_file;

  std::vector<int> tasks_list_;
  int task_num_for_init_vec;
  int task_num_for_OLF;


  // random seed
  int baseline_seed;

  // baseline_alpha
  float baseline_alpha;

  // baseline_lambda
  float baseline_lambda;
  // // use to indicate whether we will conduct task split or not, if yes, =1
  // int task_split_flag; //FIXME: not work

  int nid_debug;

  //  if the task gain is less than a certain ratio of the mean
  float mean_less_ratio;


  // number of tasks
  int num_task;

  // debug
  int debug;

  // this is used to indicate which value is used to perform OLF split;
  int which_task_value;

  // the max negative sample ratio to determine when to do task split.
  float threshold_ratio_R;

  // whether to use task gain self, otherwise, use task gain all.
  int use_task_gain_self;

  // which kind of condition we will use to determine when to do task split
  int when_task_split;

  // which kind of task split way we will use to do task split
  int how_task_split;

  // the minimal task gain, if any task has a smaller task gain, we will conduct a task split here.
  float min_task_gain;

  // the hard margin use to partition the task
  float task_gain_margin;

  // learning step size for a time
  float learning_rate;
  // minimum loss change required for a split
  float min_split_loss;
  // maximum depth of a tree
  int max_depth;
  // maximum number of leaves
  int max_leaves;
  // if using histogram based algorithm, maximum number of bins per feature
  int max_bin;
  // growing policy
  enum TreeGrowPolicy { kDepthWise = 0, kLossGuide = 1 };
  int grow_policy;
  // flag to print out detailed breakdown of runtime
  int debug_verbose;
  //----- the rest parameters are less important ----
  // minimum amount of hessian(weight) allowed in a child
  float min_child_weight;
  // L2 regularization factor
  float reg_lambda;
  // L1 regularization factor
  float reg_alpha;
  // default direction choice
  int default_direction;
  // maximum delta update we can add in weight estimation
  // this parameter can be used to stabilize update
  // default=0 means no constraint on weight delta
  float max_delta_step;
  // whether we want to do subsample
  float subsample;
  // whether to subsample columns each split, in each level
  float colsample_bylevel;
  // whether to subsample columns during tree construction
  float colsample_bytree;
  // speed optimization for dense column
  float opt_dense_col;
  // accuracy of sketch
  float sketch_eps;
  // accuracy of sketch
  float sketch_ratio;
  // leaf vector size
  int size_leaf_vector;
  // option for parallelization
  int parallel_option;
  // option to open cacheline optimization
  bool cache_opt;
  // whether to not print info during training.
  bool silent;
  // whether refresh updater needs to update the leaf values
  bool refresh_leaf;
  // auxiliary data structure
  std::vector<int> monotone_constraints;
  // gpu to use for single gpu algorithms
  int gpu_id;
  // number of GPUs to use
  int n_gpus;
  // declare the parameters
  DMLC_DECLARE_PARAMETER(TrainParam) {


    DMLC_DECLARE_FIELD(mean_less_ratio)
        .set_default(0)
        .describe("if the task gain is less than a certain ratio of the mean.");
    DMLC_DECLARE_FIELD(conduct_task_split_N_layer_before)
      .set_default(0)
      .describe("conduct_task_split_N_layer_before.");
  

    DMLC_DECLARE_FIELD(leaf_output_flag)
        .set_default(0)
        .describe("leaf_output_flag.");
    
    DMLC_DECLARE_FIELD(task_gain_output_flag)
        .set_default(0)
        .describe("task_gain_output_flag.");

    DMLC_DECLARE_FIELD(xgboost_task_gain_output_flag)
        .set_default(0)
        .describe("xgboost_task_gain_output_flag.");


        
        

    DMLC_DECLARE_FIELD(output_file)
        .set_default("./tree-leaf.info")
        .describe("output_file.");

    DMLC_DECLARE_FIELD(task_num_for_OLF)
        .set_default(21)
        .describe("task_num_for_OLF.");

    DMLC_DECLARE_FIELD(task_num_for_init_vec)
        .set_default(30)
        .describe("task_num_for_init_vec.");

    DMLC_DECLARE_FIELD(num_task)
        .set_default(30)
        .describe("number of tasks.");


    


    
    DMLC_DECLARE_FIELD(tasks_list_)
        .set_default(std::vector<int>({1, 2, 4, 5, 6, 10, 11, 12, 13, 16, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29}))
        .describe("tasks_list_");


    DMLC_DECLARE_FIELD(baseline_seed)
        .set_default(0)
        .describe("baseline_seed.");

    DMLC_DECLARE_FIELD(baseline_lambda)
        .set_default(0.5)
        .describe("baseline_lambda");
    

    DMLC_DECLARE_FIELD(debug)
        .set_default(0)
        .describe("debug.");

    DMLC_DECLARE_FIELD(nid_debug)
        .set_default(0)
        .describe("nid_debug");

        
    DMLC_DECLARE_FIELD(baseline_alpha)
        .set_default(0.2)
        .describe("baseline_alpha");
        

    // DMLC_DECLARE_FIELD(task_split_flag)
    //     .set_default(1)
    //     .describe("use to indicate whether we will conduct task split or not, if yes, =1."); //FIXME: not work
    DMLC_DECLARE_FIELD(which_task_value)
        .set_default(0)
        .describe("this is used to indicate which value is used to perform OLF split.");
    
    DMLC_DECLARE_FIELD(threshold_ratio_R)
        .set_range(0.0f, 1.0f)
        .set_default(0.4f)
        .describe("the max negative sample ratio to determine when to do task split.");
    
    DMLC_DECLARE_FIELD(task_gain_margin)
        .set_default(0.0f)
        .describe("the hard margin use to partition the task.");

    DMLC_DECLARE_FIELD(use_task_gain_self)
        .set_default(1)
        .describe("whether to use task gain self, otherwise, use task gain all.");

    DMLC_DECLARE_FIELD(when_task_split)
        .set_default(1)
        .describe(" which kind of condition we will use to determine when to do task split");

    DMLC_DECLARE_FIELD(how_task_split)
        .set_default(0)
        .describe(" which kind of task split way we will use to do task split");


    DMLC_DECLARE_FIELD(min_task_gain)
        // .set_upper_bound(0.0f)
        .set_default(-0.0f)
        .describe("the minimal task gain, if any task has a smaller task gain, we will conduct a task split here.");
    DMLC_DECLARE_FIELD(learning_rate)
        .set_lower_bound(0.0f)
        .set_default(0.3f)
        .describe("Learning rate(step size) of update.");
    DMLC_DECLARE_FIELD(min_split_loss)
        .set_lower_bound(0.0f)
        .set_default(0.0f)
        .describe(
            "Minimum loss reduction required to make a further partition.");
    DMLC_DECLARE_FIELD(debug_verbose)
        .set_lower_bound(0)
        .set_default(0)
        .describe("flag to print out detailed breakdown of runtime");
    DMLC_DECLARE_FIELD(max_depth)
        .set_lower_bound(0)
        .set_default(6)
        .describe(
            "Maximum depth of the tree; 0 indicates no limit; a limit is required "
            "for depthwise policy");
    DMLC_DECLARE_FIELD(max_leaves).set_lower_bound(0).set_default(0).describe(
        "Maximum number of leaves; 0 indicates no limit.");
    DMLC_DECLARE_FIELD(max_bin).set_lower_bound(2).set_default(256).describe(
        "if using histogram-based algorithm, maximum number of bins per feature");
    DMLC_DECLARE_FIELD(grow_policy)
        .set_default(kDepthWise)
        .add_enum("depthwise", kDepthWise)
        .add_enum("lossguide", kLossGuide)
        .describe(
            "Tree growing policy. 0: favor splitting at nodes closest to the node, "
            "i.e. grow depth-wise. 1: favor splitting at nodes with highest loss "
            "change. (cf. LightGBM)");
    DMLC_DECLARE_FIELD(min_child_weight)
        .set_lower_bound(0.0f)
        .set_default(1.0f)
        .describe("Minimum sum of instance weight(hessian) needed in a child.");
    DMLC_DECLARE_FIELD(reg_lambda)
        .set_lower_bound(0.0f)
        .set_default(1.0f)
        .describe("L2 regularization on leaf weight");
    DMLC_DECLARE_FIELD(reg_alpha)
        .set_lower_bound(0.0f)
        .set_default(0.0f)
        .describe("L1 regularization on leaf weight");
    DMLC_DECLARE_FIELD(default_direction)
        .set_default(0)
        .add_enum("learn", 0)
        .add_enum("left", 1)
        .add_enum("right", 2)
        .describe("Default direction choice when encountering a missing value");
    DMLC_DECLARE_FIELD(max_delta_step)
        .set_lower_bound(0.0f)
        .set_default(0.0f)
        .describe("Maximum delta step we allow each tree's weight estimate to be. "\
                  "If the value is set to 0, it means there is no constraint");
    DMLC_DECLARE_FIELD(subsample)
        .set_range(0.0f, 1.0f)
        .set_default(1.0f)
        .describe("Row subsample ratio of training instance.");
    DMLC_DECLARE_FIELD(colsample_bylevel)
        .set_range(0.0f, 1.0f)
        .set_default(1.0f)
        .describe("Subsample ratio of columns, resample on each level.");
    DMLC_DECLARE_FIELD(colsample_bytree)
        .set_range(0.0f, 1.0f)
        .set_default(1.0f)
        .describe("Subsample ratio of columns, resample on each tree construction.");
    DMLC_DECLARE_FIELD(opt_dense_col)
        .set_range(0.0f, 1.0f)
        .set_default(1.0f)
        .describe("EXP Param: speed optimization for dense column.");
    DMLC_DECLARE_FIELD(sketch_eps)
        .set_range(0.0f, 1.0f)
        .set_default(0.03f)
        .describe("EXP Param: Sketch accuracy of approximate algorithm.");
    DMLC_DECLARE_FIELD(sketch_ratio)
        .set_lower_bound(0.0f)
        .set_default(2.0f)
        .describe("EXP Param: Sketch accuracy related parameter of approximate algorithm.");
    DMLC_DECLARE_FIELD(size_leaf_vector)
        .set_lower_bound(0)
        .set_default(0)
        .describe("Size of leaf vectors, reserved for vector trees");
    DMLC_DECLARE_FIELD(parallel_option)
        .set_default(0)
        .describe("Different types of parallelization algorithm.");
    DMLC_DECLARE_FIELD(cache_opt)
        .set_default(true)
        .describe("EXP Param: Cache aware optimization.");
    DMLC_DECLARE_FIELD(silent)
        .set_default(false)
        .describe("Do not print information during trainig.");
    DMLC_DECLARE_FIELD(refresh_leaf)
        .set_default(true)
        .describe("Whether the refresh updater needs to update leaf values.");
    DMLC_DECLARE_FIELD(monotone_constraints)
        .set_default(std::vector<int>())
        .describe("Constraint of variable monotonicity");
    DMLC_DECLARE_FIELD(gpu_id)
        .set_lower_bound(0)
        .set_default(0)
        .describe("gpu to use for single gpu algorithms");
    DMLC_DECLARE_FIELD(n_gpus)
        .set_lower_bound(-1)
        .set_default(1)
        .describe("Number of GPUs to use for multi-gpu algorithms: -1=use all GPUs");
    // add alias of parameters
    DMLC_DECLARE_ALIAS(reg_lambda, lambda);
    DMLC_DECLARE_ALIAS(reg_alpha, alpha);
    DMLC_DECLARE_ALIAS(min_split_loss, gamma);
    DMLC_DECLARE_ALIAS(learning_rate, eta);
  }
  /*! \brief whether need forward small to big search: default right */
  inline bool NeedForwardSearch(float col_density, bool indicator) const {
    return this->default_direction == 2 ||
           (default_direction == 0 && (col_density < opt_dense_col) &&
            !indicator);
  }
  /*! \brief whether need backward big to small search: default left */
  inline bool NeedBackwardSearch(float col_density, bool indicator) const {
    return this->default_direction != 2;
  }
  /*! \brief given the loss change, whether we need to invoke pruning */
  inline bool NeedPrune(double loss_chg, int depth) const {
    return loss_chg < this->min_split_loss;
  }
  /*! \brief whether we can split with current hessian */
  inline bool CannotSplit(double sum_hess, int depth) const {
    return sum_hess < this->min_child_weight * 2.0;
  }
  /*! \brief maximum sketch size */
  inline unsigned MaxSketchSize() const {
    auto ret = static_cast<unsigned>(sketch_ratio / sketch_eps);
    CHECK_GT(ret, 0U);
    return ret;
  }
};

/*! \brief Loss functions */

// functions for L1 cost
template <typename T1, typename T2>
XGBOOST_DEVICE inline static T1 ThresholdL1(T1 w, T2 lambda) {
  if (w > +lambda) {
    return w - lambda;
  }
  if (w < -lambda) {
    return w + lambda;
  }
  return 0.0;
}

template <typename T>
XGBOOST_DEVICE inline static T Sqr(T a) { return a * a; }

// calculate the cost of loss function
template <typename TrainingParams, typename T>
XGBOOST_DEVICE inline T CalcGainGivenWeight(const TrainingParams &p, T sum_grad,
                                        T sum_hess, T w) {
  return -(2.0 * sum_grad * w + (sum_hess + p.reg_lambda) * Sqr(w));
}

// calculate the cost of loss function
template <typename TrainingParams, typename T>
XGBOOST_DEVICE inline T CalcGain(const TrainingParams &p, T sum_grad, T sum_hess) {
  if (sum_hess < p.min_child_weight) {
    return T(0.0);
}
  if (p.max_delta_step == 0.0f) {
    if (p.reg_alpha == 0.0f) {
      return Sqr(sum_grad) / (sum_hess + p.reg_lambda);
    } else {
      return Sqr(ThresholdL1(sum_grad, p.reg_alpha)) /
             (sum_hess + p.reg_lambda);
    }
  } else {
    T w = CalcWeight(p, sum_grad, sum_hess);
    T ret = sum_grad * w + T(0.5) * (sum_hess + p.reg_lambda) * Sqr(w);
    if (p.reg_alpha == 0.0f) {
      return T(-2.0) * ret;
    } else {
      return T(-2.0) * (ret + p.reg_alpha * std::abs(w));
    }
  }
}
// calculate cost of loss function with four statistics
template <typename TrainingParams, typename T>
XGBOOST_DEVICE inline T CalcGain(const TrainingParams &p, T sum_grad, T sum_hess,
                             T test_grad, T test_hess) {
  T w = CalcWeight(sum_grad, sum_hess);
  T ret = test_grad * w + 0.5 * (test_hess + p.reg_lambda) * Sqr(w);
  if (p.reg_alpha == 0.0f) {
    return -2.0 * ret;
  } else {
    return -2.0 * (ret + p.reg_alpha * std::abs(w));
  }
}

// calculate weight given the statistics
template <typename TrainingParams, typename T>
XGBOOST_DEVICE inline T CalcWeight(const TrainingParams &p, T sum_grad,
                               T sum_hess) {
  if (sum_hess < p.min_child_weight) {
    return 0.0;
}
  T dw;
  if (p.reg_alpha == 0.0f) {
    dw = -sum_grad / (sum_hess + p.reg_lambda);
  } else {
    dw = -ThresholdL1(sum_grad, p.reg_alpha) / (sum_hess + p.reg_lambda);
  }
  if (p.max_delta_step != 0.0f) {
    if (dw > p.max_delta_step) {
      dw = p.max_delta_step;
}
    if (dw < -p.max_delta_step) {
      dw = -p.max_delta_step;
}
  }
  return dw;
}

template <typename TrainingParams, typename GpairT>
XGBOOST_DEVICE inline float CalcWeight(const TrainingParams &p, GpairT sum_grad) {
  return CalcWeight(p, sum_grad.GetGrad(), sum_grad.GetHess());
}

/*! \brief core statistics used for tree construction */
struct XGBOOST_ALIGNAS(16) GradStats {
  /*! \brief sum gradient statistics */
  double sum_grad;
  /*! \brief sum hessian statistics */
  double sum_hess;
  /*!
   * \brief whether this is simply statistics and we only need to call
   *   Add(gpair), instead of Add(gpair, info, ridx)
   */
  static const int kSimpleStats = 1;
  /*! \brief constructor, the object must be cleared during construction */
  explicit GradStats(const TrainParam& param) { this->Clear(); }

  template <typename GpairT>
  XGBOOST_DEVICE explicit GradStats(const GpairT &sum)
      : sum_grad(sum.GetGrad()), sum_hess(sum.GetHess()) {}
  /*! \brief clear the statistics */
  inline void Clear() { sum_grad = sum_hess = 0.0f; }
  /*! \brief check if necessary information is ready */
  inline static void CheckInfo(const MetaInfo& info) {}
  /*!
   * \brief accumulate statistics
   * \param p the gradient pair
   */
  inline void Add(GradientPair p) { this->Add(p.GetGrad(), p.GetHess()); }
  /*!
   * \brief accumulate statistics, more complicated version
   * \param gpair the vector storing the gradient statistics
   * \param info the additional information
   * \param ridx instance index of this instance
   */
  inline void Add(const std::vector<GradientPair>& gpair, const MetaInfo& info,
                  bst_uint ridx) {
    const GradientPair& b = gpair[ridx];
    this->Add(b.GetGrad(), b.GetHess());
  }
  /*! \brief calculate leaf weight */
  template <typename ParamT>
  XGBOOST_DEVICE inline double CalcWeight(const ParamT &param) const {
    return xgboost::tree::CalcWeight(param, sum_grad, sum_hess);
  }
  /*! \brief calculate gain of the solution */
template <typename ParamT>
  inline double CalcGain(const ParamT& param) const {
    return xgboost::tree::CalcGain(param, sum_grad, sum_hess);
  }
  /*! \brief add statistics to the data */
  inline void Add(const GradStats& b) {
    sum_grad += b.sum_grad;
    sum_hess += b.sum_hess;
  }
  /*! \brief same as add, reduce is used in All Reduce */
  inline static void Reduce(GradStats& a, const GradStats& b) { // NOLINT(*)
    a.Add(b);
  }
  /*! \brief set current value to a - b */
  inline void SetSubstract(const GradStats& a, const GradStats& b) {
    sum_grad = a.sum_grad - b.sum_grad;
    sum_hess = a.sum_hess - b.sum_hess;
  }
  /*! \return whether the statistics is not used yet */
  inline bool Empty() const { return sum_hess == 0.0; }
  /*! \brief set leaf vector value based on statistics */
  inline void SetLeafVec(const TrainParam& param, bst_float* vec) const {}
  // constructor to allow inheritance
  GradStats() = default;
  /*! \brief add statistics to the data */
  inline void Add(double grad, double hess) {
    sum_grad += grad;
    sum_hess += hess;
  }
};

struct NoConstraint {
  inline static void Init(TrainParam *param, unsigned num_feature) {
    param->monotone_constraints.resize(num_feature, 0);
  }
  inline double CalcSplitGain(const TrainParam &param, int constraint,
                              GradStats left, GradStats right) const {
    return left.CalcGain(param) + right.CalcGain(param);
  }
  inline double CalcWeight(const TrainParam &param, GradStats stats) const {
    return stats.CalcWeight(param);
  }
  inline double CalcGain(const TrainParam &param, GradStats stats) const {
    return stats.CalcGain(param);
  }
  inline void SetChild(const TrainParam &param, bst_uint split_index,
                       GradStats left, GradStats right, NoConstraint *cleft,
                       NoConstraint *cright) {}
};

struct ValueConstraint {
  double lower_bound;
  double upper_bound;
  XGBOOST_DEVICE ValueConstraint()
      : lower_bound(-std::numeric_limits<double>::max()),
        upper_bound(std::numeric_limits<double>::max()) {}
  inline static void Init(TrainParam *param, unsigned num_feature) {
    param->monotone_constraints.resize(num_feature, 0);
  }
template <typename ParamT>
  XGBOOST_DEVICE inline double CalcWeight(const ParamT &param, GradStats stats) const {
    double w = stats.CalcWeight(param);
    if (w < lower_bound) {
      return lower_bound;
    }
    if (w > upper_bound) {
      return upper_bound;
    }
    return w;
  }

template <typename ParamT>
  XGBOOST_DEVICE inline double CalcGain(const ParamT &param, GradStats stats) const {
    return CalcGainGivenWeight(param, stats.sum_grad, stats.sum_hess,
                               CalcWeight(param, stats));
  }

template <typename ParamT>
  XGBOOST_DEVICE inline double CalcSplitGain(const ParamT &param, int constraint,
                              GradStats left, GradStats right) const {
    const double negative_infinity = -std::numeric_limits<double>::infinity();
    double wleft = CalcWeight(param, left);
    double wright = CalcWeight(param, right);
    double gain =
        CalcGainGivenWeight(param, left.sum_grad, left.sum_hess, wleft) +
        CalcGainGivenWeight(param, right.sum_grad, right.sum_hess, wright);
    if (constraint == 0) {
      return gain;
    } else if (constraint > 0) {
      return wleft <= wright ? gain : negative_infinity;
    } else {
      return wleft >= wright ? gain : negative_infinity;
    }
  }

  inline void SetChild(const TrainParam &param, bst_uint split_index,
                       GradStats left, GradStats right, ValueConstraint *cleft,
                       ValueConstraint *cright) {
    int c = param.monotone_constraints.at(split_index);
    *cleft = *this;
    *cright = *this;
    if (c == 0) {
      return;
}
    double wleft = CalcWeight(param, left);
    double wright = CalcWeight(param, right);
    double mid = (wleft + wright) / 2;
    CHECK(!std::isnan(mid));
    if (c < 0) {
      cleft->lower_bound = mid;
      cright->upper_bound = mid;
    } else {
      cleft->upper_bound = mid;
      cright->lower_bound = mid;
    }
  }
};

/*!
 * \brief statistics that is helpful to store
 *   and represent a split solution for the tree
 */
struct SplitEntry {
  /*! \brief loss change after split this node */
  bst_float loss_chg{0.0f};
  /*! \brief split index */
  unsigned sindex{0};
  /*! \brief split value */
  bst_float split_value{0.0f};
  /*! \brief constructor */
  SplitEntry()  = default;
  /*!
   * \brief decides whether we can replace current entry with the given
   * statistics
   *   This function gives better priority to lower index when loss_chg ==
   * new_loss_chg.
   *   Not the best way, but helps to give consistent result during multi-thread
   * execution.
   * \param new_loss_chg the loss reduction get through the split
   * \param split_index the feature index where the split is on
   */
  inline bool NeedReplace(bst_float new_loss_chg, unsigned split_index) const {
    if (this->SplitIndex() <= split_index) {
      return new_loss_chg > this->loss_chg;
    } else {
      return !(this->loss_chg > new_loss_chg);
    }
  }
  /*!
   * \brief update the split entry, replace it if e is better
   * \param e candidate split solution
   * \return whether the proposed split is better and can replace current split
   */
  inline bool Update(const SplitEntry &e) {
    if (this->NeedReplace(e.loss_chg, e.SplitIndex())) {
      this->loss_chg = e.loss_chg;
      this->sindex = e.sindex;
      this->split_value = e.split_value;
      return true;
    } else {
      return false;
    }
  }
  /*!
   * \brief update the split entry, replace it if e is better
   * \param new_loss_chg loss reduction of new candidate
   * \param split_index feature index to split on
   * \param new_split_value the split point
   * \param default_left whether the missing value goes to left
   * \return whether the proposed split is better and can replace current split
   */
  inline bool Update(bst_float new_loss_chg, unsigned split_index,
                     bst_float new_split_value, bool default_left) {
    if (this->NeedReplace(new_loss_chg, split_index)) {
      this->loss_chg = new_loss_chg;
      if (default_left) {
        split_index |= (1U << 31);
}
      this->sindex = split_index;
      this->split_value = new_split_value;
      return true;
    } else {
      return false;
    }
  }
  /*! \brief same as update, used by AllReduce*/
  inline static void Reduce(SplitEntry &dst, // NOLINT(*)
                            const SplitEntry &src) { // NOLINT(*)
    dst.Update(src);
  }
  /*!\return feature index to split on */
  inline unsigned SplitIndex() const { return sindex & ((1U << 31) - 1U); }
  /*!\return whether missing value goes to left branch */
  inline bool DefaultLeft() const { return (sindex >> 31) != 0; }
};

}  // namespace tree
}  // namespace xgboost

// define string serializer for vector, to get the arguments
namespace std {
inline std::ostream &operator<<(std::ostream &os, const std::vector<int> &t) {
  os << '(';
  for (auto it = t.begin(); it != t.end(); ++it) {
    if (it != t.begin()) {
      os << ',';
}
    os << *it;
  }
  // python style tuple
  if (t.size() == 1) {
    os << ',';
}
  os << ')';
  return os;
}

inline std::istream &operator>>(std::istream &is, std::vector<int> &t) {
  // get (
  while (true) {
    char ch = is.peek();
    if (isdigit(ch)) {
      int idx;
      if (is >> idx) {
        t.assign(&idx, &idx + 1);
      }
      return is;
    }
    is.get();
    if (ch == '(') {
      break;
}
    if (!isspace(ch)) {
      is.setstate(std::ios::failbit);
      return is;
    }
  }
  int idx;
  std::vector<int> tmp;
  while (is >> idx) {
    tmp.push_back(idx);
    char ch;
    do {
      ch = is.get();
    } while (isspace(ch));
    if (ch == 'L') {
      ch = is.get();
    }
    if (ch == ',') {
      while (true) {
        ch = is.peek();
        if (isspace(ch)) {
          is.get();
          continue;
        }
        if (ch == ')') {
          is.get();
          break;
        }
        break;
      }
      if (ch == ')') {
        break;
}
    } else if (ch == ')') {
      break;
    } else {
      is.setstate(std::ios::failbit);
      return is;
    }
  }
  t.assign(tmp.begin(), tmp.end());
  return is;
}
}  // namespace std

#endif  // XGBOOST_TREE_PARAM_H_
