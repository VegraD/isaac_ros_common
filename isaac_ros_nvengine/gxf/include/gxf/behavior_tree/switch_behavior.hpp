/*
Copyright (c) 2021, NVIDIA CORPORATION. All rights reserved.

NVIDIA CORPORATION and its licensors retain all intellectual property
and proprietary rights in and to this software, related documentation
and any modifications thereto. Any use, reproduction, disclosure or
distribution of this software and related documentation without an express
license agreement from NVIDIA CORPORATION is strictly prohibited.
*/

#ifndef NVIDIA_GXF_BT_SWITCH_BEHAVIOR_HPP_
#define NVIDIA_GXF_BT_SWITCH_BEHAVIOR_HPP_

#include <vector>

#include "common/fixed_vector.hpp"
#include "gxf/std/codelet.hpp"
#include "gxf/std/controller.hpp"
#include "gxf/std/scheduling_terms.hpp"

namespace nvidia {
namespace gxf {

// Switch Behavior
// Runs the child entity with the index defined as desired_behavior.
class SwitchBehavior : public Codelet {
 public:
  virtual ~SwitchBehavior() = default;

  gxf_result_t registerInterface(Registrar* registrar) override;
  gxf_result_t initialize() override;
  gxf_result_t start() override { return GXF_SUCCESS; }
  gxf_result_t tick() override;
  gxf_result_t stop() override { return GXF_SUCCESS; }

 private:
  // parent codelet points to children's scheduling terms to schedule child
  // entities
  // Parameter<std::vector<Handle<nvidia::gxf::BTSchedulingTerm> > > children_;
  // std::vector<Handle<nvidia::gxf::BTSchedulingTerm> > children;
  Parameter<FixedVector<Handle<nvidia::gxf::BTSchedulingTerm>, kMaxComponents> >
      children_;
  FixedVector<Handle<nvidia::gxf::BTSchedulingTerm>, kMaxComponents> children;
  std::vector<gxf_uid_t> children_eid;
  // its own scheduling term to start/stop itself
  Parameter<Handle<nvidia::gxf::BTSchedulingTerm> > s_term_;
  Handle<nvidia::gxf::BTSchedulingTerm> s_term;

  // the child entity to switch to. this child entity will run when this parent
  // entity runs and the parent entity will return this child entity's behavior
  // status may not be empty
  Parameter<size_t> desired_behavior_;
  size_t getNumChildren() const;
  entity_state_t GetChildStatus(size_t child_id);
  gxf_result_t startChild(size_t child_id);
  size_t current_child_id;
  SchedulingConditionType ready_conditions;
  SchedulingConditionType never_conditions;
};

}  // namespace gxf
}  // namespace nvidia

#endif  // NVIDIA_GXF_BT_SWITCH_BEHAVIOR_HPP_
