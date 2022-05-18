// Copyright 2010-2021 Google LLC
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "ortools/pdlp/solvers_proto_validation.h"

#include <limits>
#include <string>

#include "absl/status/status.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "ortools/pdlp/solvers.pb.h"

namespace operations_research::pdlp {
namespace {

using ::testing::HasSubstr;

TEST(ValidateTerminationCriteria, DefaultIsValid) {
  TerminationCriteria criteria;
  const absl::Status status = ValidateTerminationCriteria(criteria);
  EXPECT_TRUE(status.ok()) << status;
}

TEST(ValidateTerminationCriteria, BadOptimalityNorm) {
  TerminationCriteria criteria;
  criteria.set_optimality_norm(OPTIMALITY_NORM_UNSPECIFIED);
  const absl::Status status = ValidateTerminationCriteria(criteria);
  EXPECT_EQ(status.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status.message(), HasSubstr("optimality_norm"));
}

TEST(ValidateTerminationCriteria, BadEpsOptimalAbsolute) {
  TerminationCriteria criteria_negative;
  criteria_negative.set_eps_optimal_absolute(-1.0);
  const absl::Status status_negative =
      ValidateTerminationCriteria(criteria_negative);
  EXPECT_EQ(status_negative.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_negative.message(), HasSubstr("eps_optimal_absolute"));

  TerminationCriteria criteria_nan;
  criteria_nan.set_eps_optimal_absolute(
      std::numeric_limits<double>::quiet_NaN());
  const absl::Status status_nan = ValidateTerminationCriteria(criteria_nan);
  EXPECT_EQ(status_nan.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_nan.message(), HasSubstr("eps_optimal_absolute"));
}

TEST(ValidateTerminationCriteria, BadEpsOptimalRelative) {
  TerminationCriteria criteria_negative;
  criteria_negative.set_eps_optimal_relative(-1.0);
  const absl::Status status_negative =
      ValidateTerminationCriteria(criteria_negative);
  EXPECT_EQ(status_negative.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_negative.message(), HasSubstr("eps_optimal_relative"));

  TerminationCriteria criteria_nan;
  criteria_nan.set_eps_optimal_relative(
      std::numeric_limits<double>::quiet_NaN());
  const absl::Status status_nan = ValidateTerminationCriteria(criteria_nan);
  EXPECT_EQ(status_nan.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_nan.message(), HasSubstr("eps_optimal_relative"));
}

TEST(ValidateTerminationCriteria, BadEpsPriamlInfeasible) {
  TerminationCriteria criteria_negative;
  criteria_negative.set_eps_primal_infeasible(-1.0);
  const absl::Status status_negative =
      ValidateTerminationCriteria(criteria_negative);
  EXPECT_EQ(status_negative.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_negative.message(), HasSubstr("eps_primal_infeasible"));

  TerminationCriteria criteria_nan;
  criteria_nan.set_eps_primal_infeasible(
      std::numeric_limits<double>::quiet_NaN());
  const absl::Status status_nan = ValidateTerminationCriteria(criteria_nan);
  EXPECT_EQ(status_nan.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_nan.message(), HasSubstr("eps_primal_infeasible"));
}

TEST(ValidateTerminationCriteria, BadEpsDualInfeasible) {
  TerminationCriteria criteria_negative;
  criteria_negative.set_eps_dual_infeasible(-1.0);
  const absl::Status status_negative =
      ValidateTerminationCriteria(criteria_negative);
  EXPECT_EQ(status_negative.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_negative.message(), HasSubstr("eps_dual_infeasible"));

  TerminationCriteria criteria_nan;
  criteria_nan.set_eps_dual_infeasible(
      std::numeric_limits<double>::quiet_NaN());
  const absl::Status status_nan = ValidateTerminationCriteria(criteria_nan);
  EXPECT_EQ(status_nan.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_nan.message(), HasSubstr("eps_dual_infeasible"));
}

TEST(ValidateTerminationCriteria, BadTimeSecLimit) {
  TerminationCriteria criteria_negative;
  criteria_negative.set_time_sec_limit(-1.0);
  const absl::Status status_negative =
      ValidateTerminationCriteria(criteria_negative);
  EXPECT_EQ(status_negative.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_negative.message(), HasSubstr("time_sec_limit"));

  TerminationCriteria criteria_nan;
  criteria_nan.set_time_sec_limit(std::numeric_limits<double>::quiet_NaN());
  const absl::Status status_nan = ValidateTerminationCriteria(criteria_nan);
  EXPECT_EQ(status_nan.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_nan.message(), HasSubstr("time_sec_limit"));
}

TEST(ValidateTerminationCriteria, BadIterationLimit) {
  TerminationCriteria criteria;
  criteria.set_iteration_limit(-1);
  const absl::Status status = ValidateTerminationCriteria(criteria);
  EXPECT_EQ(status.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status.message(), HasSubstr("iteration_limit"));
}

TEST(ValidateTerminationCriteria, BadKktMatrixPassLimit) {
  TerminationCriteria criteria_negative;
  criteria_negative.set_kkt_matrix_pass_limit(-1.0);
  const absl::Status status_negative =
      ValidateTerminationCriteria(criteria_negative);
  EXPECT_EQ(status_negative.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_negative.message(), HasSubstr("kkt_matrix_pass_limit"));

  TerminationCriteria criteria_nan;
  criteria_nan.set_kkt_matrix_pass_limit(
      std::numeric_limits<double>::quiet_NaN());
  const absl::Status status_nan = ValidateTerminationCriteria(criteria_nan);
  EXPECT_EQ(status_nan.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_nan.message(), HasSubstr("kkt_matrix_pass_limit"));
}

TEST(ValidateAdaptiveLinesearchParams, DefaultIsValid) {
  AdaptiveLinesearchParams params;
  const absl::Status status = ValidateAdaptiveLinesearchParams(params);
  EXPECT_TRUE(status.ok()) << status;
}

TEST(ValidateAdaptiveLinesearchParams, BadReductionExponent) {
  AdaptiveLinesearchParams params_low;
  params_low.set_step_size_reduction_exponent(0.0);
  const absl::Status status_low = ValidateAdaptiveLinesearchParams(params_low);
  EXPECT_EQ(status_low.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_low.message(), HasSubstr("step_size_reduction_exponent"));

  AdaptiveLinesearchParams params_nan;
  params_nan.set_step_size_reduction_exponent(
      std::numeric_limits<double>::quiet_NaN());
  const absl::Status status_nan = ValidateAdaptiveLinesearchParams(params_nan);
  EXPECT_EQ(status_nan.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_nan.message(), HasSubstr("step_size_reduction_exponent"));
}

TEST(ValidateAdaptiveLinesearchParams, BadGrowthExponent) {
  AdaptiveLinesearchParams params_low;
  params_low.set_step_size_growth_exponent(0.0);
  const absl::Status status_low = ValidateAdaptiveLinesearchParams(params_low);
  EXPECT_EQ(status_low.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_low.message(), HasSubstr("step_size_growth_exponent"));

  AdaptiveLinesearchParams params_nan;
  params_nan.set_step_size_growth_exponent(
      std::numeric_limits<double>::quiet_NaN());
  const absl::Status status_nan = ValidateAdaptiveLinesearchParams(params_nan);
  EXPECT_EQ(status_nan.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_nan.message(), HasSubstr("step_size_growth_exponent"));
}

TEST(ValidateMalitskyPockParams, DefaultIsValid) {
  MalitskyPockParams params;
  const absl::Status status = ValidateMalitskyPockParams(params);
  EXPECT_TRUE(status.ok()) << status;
}

TEST(ValidateMalitskyPockParams, BadDownscalingFactor) {
  MalitskyPockParams params_low;
  params_low.set_step_size_downscaling_factor(0.0);
  const absl::Status status_low = ValidateMalitskyPockParams(params_low);
  EXPECT_EQ(status_low.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_low.message(), HasSubstr("step_size_downscaling_factor"));

  MalitskyPockParams params_high;
  params_high.set_step_size_downscaling_factor(1.0);
  const absl::Status status_high = ValidateMalitskyPockParams(params_high);
  EXPECT_EQ(status_high.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_high.message(), HasSubstr("step_size_downscaling_factor"));

  MalitskyPockParams params_nan;
  params_nan.set_step_size_downscaling_factor(
      std::numeric_limits<double>::quiet_NaN());
  const absl::Status status_nan = ValidateMalitskyPockParams(params_nan);
  EXPECT_EQ(status_nan.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_nan.message(), HasSubstr("step_size_downscaling_factor"));
}

TEST(ValidateMalitskyPockParams, BadContractionFactor) {
  MalitskyPockParams params_low;
  params_low.set_linesearch_contraction_factor(0.0);
  const absl::Status status_low = ValidateMalitskyPockParams(params_low);
  EXPECT_EQ(status_low.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_low.message(), HasSubstr("linesearch_contraction_factor"));

  MalitskyPockParams params_high;
  params_high.set_linesearch_contraction_factor(1.0);
  const absl::Status status_high = ValidateMalitskyPockParams(params_high);
  EXPECT_EQ(status_high.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_high.message(),
              HasSubstr("linesearch_contraction_factor"));

  MalitskyPockParams params_nan;
  params_nan.set_linesearch_contraction_factor(
      std::numeric_limits<double>::quiet_NaN());
  const absl::Status status_nan = ValidateMalitskyPockParams(params_nan);
  EXPECT_EQ(status_nan.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_nan.message(), HasSubstr("linesearch_contraction_factor"));
}

TEST(ValidateMalitskyPockParams, BadStepSizeInterpolation) {
  MalitskyPockParams params_negative;
  params_negative.set_step_size_interpolation(-1.0);
  const absl::Status status_negative =
      ValidateMalitskyPockParams(params_negative);
  EXPECT_EQ(status_negative.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_negative.message(), HasSubstr("step_size_interpolation"));

  MalitskyPockParams params_nan;
  params_nan.set_step_size_interpolation(
      std::numeric_limits<double>::quiet_NaN());
  const absl::Status status_nan = ValidateMalitskyPockParams(params_nan);
  EXPECT_EQ(status_nan.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_nan.message(), HasSubstr("step_size_interpolation"));
}

TEST(ValidatePrimalDualHybridGradientParams, DefaultIsValid) {
  PrimalDualHybridGradientParams params;
  const absl::Status status = ValidatePrimalDualHybridGradientParams(params);
  EXPECT_TRUE(status.ok()) << status;
}

TEST(ValidatePrimalDualHybridGradientParams, BadTerminationCriteria) {
  PrimalDualHybridGradientParams params;
  params.mutable_termination_criteria()->set_eps_dual_infeasible(-1.0);
  const absl::Status status = ValidatePrimalDualHybridGradientParams(params);
  EXPECT_EQ(status.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status.message(), HasSubstr("eps_dual_infeasible"));
}

TEST(ValidatePrimalDualHybridGradientParams, BadNumThreads) {
  PrimalDualHybridGradientParams params;
  params.set_num_threads(0);
  const absl::Status status = ValidatePrimalDualHybridGradientParams(params);
  EXPECT_EQ(status.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status.message(), HasSubstr("num_threads"));
}

TEST(ValidatePrimalDualHybridGradientParams, BadVerbosityLevel) {
  PrimalDualHybridGradientParams params;
  params.set_verbosity_level(-1);
  const absl::Status status = ValidatePrimalDualHybridGradientParams(params);
  EXPECT_EQ(status.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status.message(), HasSubstr("verbosity_level"));
}

TEST(ValidatePrimalDualHybridGradientParams, BadMajorIterationFrequency) {
  PrimalDualHybridGradientParams params;
  params.set_major_iteration_frequency(0);
  const absl::Status status = ValidatePrimalDualHybridGradientParams(params);
  EXPECT_EQ(status.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status.message(), HasSubstr("major_iteration_frequency"));
}

TEST(ValidatePrimalDualHybridGradientParams, BadTerminationCheckFrequency) {
  PrimalDualHybridGradientParams params;
  params.set_termination_check_frequency(0);
  const absl::Status status = ValidatePrimalDualHybridGradientParams(params);
  EXPECT_EQ(status.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status.message(), HasSubstr("termination_check_frequency"));
}

TEST(ValidatePrimalDualHybridGradientParams, BadRestartStrategy) {
  PrimalDualHybridGradientParams params;
  params.set_restart_strategy(
      PrimalDualHybridGradientParams::RESTART_STRATEGY_UNSPECIFIED);
  const absl::Status status = ValidatePrimalDualHybridGradientParams(params);
  EXPECT_EQ(status.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status.message(), HasSubstr("restart_strategy"));
}

TEST(ValidatePrimalDualHybridGradientParams, BadPrimalWeightUpdateSmoothing) {
  PrimalDualHybridGradientParams params_high;
  params_high.set_primal_weight_update_smoothing(1.1);
  const absl::Status status_high =
      ValidatePrimalDualHybridGradientParams(params_high);
  EXPECT_EQ(status_high.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_high.message(),
              HasSubstr("primal_weight_update_smoothing"));

  PrimalDualHybridGradientParams params_low;
  params_low.set_primal_weight_update_smoothing(-0.1);
  const absl::Status status_low =
      ValidatePrimalDualHybridGradientParams(params_low);
  EXPECT_EQ(status_low.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_low.message(),
              HasSubstr("primal_weight_update_smoothing"));

  PrimalDualHybridGradientParams params_nan;
  params_nan.set_primal_weight_update_smoothing(
      std::numeric_limits<double>::quiet_NaN());
  const absl::Status status_nan =
      ValidatePrimalDualHybridGradientParams(params_nan);
  EXPECT_EQ(status_nan.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_nan.message(),
              HasSubstr("primal_weight_update_smoothing"));
}

TEST(ValidatePrimalDualHybridGradientParams, BadInitialPrimalWeight) {
  PrimalDualHybridGradientParams params_negative;
  params_negative.set_initial_primal_weight(-1.0);
  const absl::Status status_negative =
      ValidatePrimalDualHybridGradientParams(params_negative);
  EXPECT_EQ(status_negative.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_negative.message(), HasSubstr("initial_primal_weight"));

  PrimalDualHybridGradientParams params_nan;
  params_nan.set_initial_primal_weight(
      std::numeric_limits<double>::quiet_NaN());
  const absl::Status status_nan =
      ValidatePrimalDualHybridGradientParams(params_nan);
  EXPECT_EQ(status_nan.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_nan.message(), HasSubstr("initial_primal_weight"));
}

TEST(ValidatePrimalDualHybridGradientParams, BadLInfRuizIterations) {
  PrimalDualHybridGradientParams params;
  params.set_l_inf_ruiz_iterations(-1);
  const absl::Status status_low =
      ValidatePrimalDualHybridGradientParams(params);
  EXPECT_EQ(status_low.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_low.message(), HasSubstr("l_inf_ruiz_iterations"));

  params.set_l_inf_ruiz_iterations(1000);
  const absl::Status status_high =
      ValidatePrimalDualHybridGradientParams(params);
  EXPECT_EQ(status_high.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_high.message(), HasSubstr("l_inf_ruiz_iterations"));
}

TEST(ValidatePrimalDualHybridGradientParams, BadSufficientReductionForRestart) {
  PrimalDualHybridGradientParams params_high;
  params_high.set_sufficient_reduction_for_restart(1.0);
  const absl::Status status_high =
      ValidatePrimalDualHybridGradientParams(params_high);
  EXPECT_EQ(status_high.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_high.message(),
              HasSubstr("sufficient_reduction_for_restart"));

  PrimalDualHybridGradientParams params_low;
  params_low.set_sufficient_reduction_for_restart(0.0);
  const absl::Status status_low =
      ValidatePrimalDualHybridGradientParams(params_low);
  EXPECT_EQ(status_low.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_low.message(),
              HasSubstr("sufficient_reduction_for_restart"));

  PrimalDualHybridGradientParams params_nan;
  params_nan.set_sufficient_reduction_for_restart(
      std::numeric_limits<double>::quiet_NaN());
  const absl::Status status_nan =
      ValidatePrimalDualHybridGradientParams(params_nan);
  EXPECT_EQ(status_nan.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_nan.message(),
              HasSubstr("sufficient_reduction_for_restart"));
}

TEST(ValidatePrimalDualHybridGradientParams, BadNecessaryReductionForRestart) {
  PrimalDualHybridGradientParams params_high;
  params_high.set_necessary_reduction_for_restart(1.0);
  const absl::Status status_high =
      ValidatePrimalDualHybridGradientParams(params_high);
  EXPECT_EQ(status_high.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_high.message(),
              HasSubstr("necessary_reduction_for_restart"));

  PrimalDualHybridGradientParams params_low;
  params_low.set_sufficient_reduction_for_restart(0.5);
  params_low.set_necessary_reduction_for_restart(0.4);
  const absl::Status status_low =
      ValidatePrimalDualHybridGradientParams(params_low);
  EXPECT_EQ(status_low.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_low.message(),
              HasSubstr("necessary_reduction_for_restart"));

  PrimalDualHybridGradientParams params_nan;
  params_nan.set_necessary_reduction_for_restart(
      std::numeric_limits<double>::quiet_NaN());
  const absl::Status status_nan =
      ValidatePrimalDualHybridGradientParams(params_nan);
  EXPECT_EQ(status_nan.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_nan.message(),
              HasSubstr("necessary_reduction_for_restart"));
}

TEST(ValidatePrimalDualHybridGradientParams, BadLinesearchRule) {
  PrimalDualHybridGradientParams params;
  params.set_linesearch_rule(
      PrimalDualHybridGradientParams::LINESEARCH_RULE_UNSPECIFIED);
  const absl::Status status = ValidatePrimalDualHybridGradientParams(params);
  EXPECT_EQ(status.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status.message(), HasSubstr("linesearch_rule"));
}

TEST(ValidatePrimalDualHybridGradientParams, BadAdaptiveLinesearchParameters) {
  PrimalDualHybridGradientParams params;
  params.mutable_adaptive_linesearch_parameters()
      ->set_step_size_reduction_exponent(-1.0);
  const absl::Status status = ValidatePrimalDualHybridGradientParams(params);
  EXPECT_EQ(status.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status.message(), HasSubstr("step_size_reduction_exponent"));
}

TEST(ValidatePrimalDualHybridGradientParams, BadMalitskyPockParameters) {
  PrimalDualHybridGradientParams params;
  params.mutable_malitsky_pock_parameters()->set_linesearch_contraction_factor(
      -1.0);
  const absl::Status status = ValidatePrimalDualHybridGradientParams(params);
  EXPECT_EQ(status.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status.message(), HasSubstr("linesearch_contraction_factor"));
}

TEST(ValidatePrimalDualHybridGradientParams, BadInitialStepSizeScaling) {
  PrimalDualHybridGradientParams params_negative;
  params_negative.set_initial_step_size_scaling(-1.0);
  const absl::Status status_negative =
      ValidatePrimalDualHybridGradientParams(params_negative);
  EXPECT_EQ(status_negative.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_negative.message(),
              HasSubstr("initial_step_size_scaling"));

  PrimalDualHybridGradientParams params_nan;
  params_nan.set_initial_step_size_scaling(
      std::numeric_limits<double>::quiet_NaN());
  const absl::Status status_nan =
      ValidatePrimalDualHybridGradientParams(params_nan);
  EXPECT_EQ(status_nan.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_nan.message(), HasSubstr("initial_step_size_scaling"));
}

TEST(ValidatePrimalDualHybridGradientParams,
     BadInfiniteConstraintBoundThreshold) {
  PrimalDualHybridGradientParams params_negative;
  params_negative.set_infinite_constraint_bound_threshold(-1.0);
  const absl::Status status_negative =
      ValidatePrimalDualHybridGradientParams(params_negative);
  EXPECT_EQ(status_negative.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_negative.message(),
              HasSubstr("infinite_constraint_bound_threshold"));

  PrimalDualHybridGradientParams params_nan;
  params_nan.set_infinite_constraint_bound_threshold(
      std::numeric_limits<double>::quiet_NaN());
  const absl::Status status_nan =
      ValidatePrimalDualHybridGradientParams(params_nan);
  EXPECT_EQ(status_nan.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_nan.message(),
              HasSubstr("infinite_constraint_bound_threshold"));
}

TEST(ValidatePrimalDualHybridGradientParams,
     BadDiagonalTrustRegionSolverTolerance) {
  PrimalDualHybridGradientParams params_negative;
  params_negative.set_diagonal_qp_trust_region_solver_tolerance(-1.0);
  const absl::Status status_negative =
      ValidatePrimalDualHybridGradientParams(params_negative);
  EXPECT_EQ(status_negative.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_negative.message(),
              HasSubstr("diagonal_qp_trust_region_solver_tolerance"));

  PrimalDualHybridGradientParams params_nan;
  params_nan.set_diagonal_qp_trust_region_solver_tolerance(
      std::numeric_limits<double>::quiet_NaN());
  const absl::Status status_nan =
      ValidatePrimalDualHybridGradientParams(params_nan);
  EXPECT_EQ(status_nan.code(), absl::StatusCode::kInvalidArgument);
  EXPECT_THAT(status_nan.message(),
              HasSubstr("diagonal_qp_trust_region_solver_tolerance"));
}

}  // namespace
}  // namespace operations_research::pdlp
