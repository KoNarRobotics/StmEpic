

#include "motor.hpp"
#include "stmepic.hpp"

using namespace stmepic::motor;
using namespace stmepic;
using namespace stmepic::gpio;

MotorClosedLoop::MotorClosedLoop(MotorBase& _motor,
                                 encoders::EncoderBase* _encoder_pos,
                                 encoders::EncoderBase* _encoder_vel,
                                 encoders::EncoderBase* _encoder_torque)
: motor(_motor), encoder_pos(_encoder_pos), encoder_vel(_encoder_vel),
  encoder_torque(_encoder_torque) {
}

void MotorClosedLoop::init() {
  motor.init();
}

float MotorClosedLoop::get_velocity() const {
  if(encoder_vel != nullptr)
    return encoder_vel->get_velocity();
  else
    return motor.get_velocity();
}

float MotorClosedLoop::get_torque() const {
  if(encoder_torque != nullptr)
    return encoder_torque->get_torque();
  else
    return motor.get_torque();
}

float MotorClosedLoop::get_position() const {
  if(encoder_pos != nullptr)
    return encoder_pos->get_angle();
  else
    return motor.get_position();
}

float MotorClosedLoop::get_absolute_position() const {
  if(encoder_pos != nullptr)
    return encoder_pos->get_absoulute_angle();
  else
    return motor.get_absolute_position();
}

float MotorClosedLoop::get_gear_ratio() const {
  return motor.get_gear_ratio();
}

void MotorClosedLoop::set_velocity(float speed) {
  motor.set_velocity(speed);
}

void MotorClosedLoop::set_torque(float torque) {
  motor.set_torque(torque);
}

void MotorClosedLoop::set_position(float position) {
  motor.set_position(position);
}

void MotorClosedLoop::set_enable(bool enable) {
  motor.set_enable(enable);
}

void MotorClosedLoop::set_gear_ratio(float gear_ratio) {
  motor.set_gear_ratio(gear_ratio);
}

void MotorClosedLoop::set_max_velocity(float max_velocity) {
  motor.set_max_velocity(max_velocity);
}

void MotorClosedLoop::set_min_velocity(float min_velocity) {
  motor.set_min_velocity(min_velocity);
}

void MotorClosedLoop::set_reverse(bool reverse) {
  motor.set_reverse(reverse);
}

bool MotorClosedLoop::device_ok() {
  motor.device_ok();
}

Result<bool> MotorClosedLoop::device_is_connected() {
  return motor.device_is_connected();
}

[[nodiscard]] Result<DeviceStatus> MotorClosedLoop::device_get_status() {
  return motor.device_get_status();
}

[[nodiscard]] Status MotorClosedLoop::device_reset() {
  return motor.device_reset();
}

[[nodiscard]] Status MotorClosedLoop::device_start() {
  return motor.device_start();
}

[[nodiscard]] Status MotorClosedLoop::device_stop() {
  return motor.device_stop();
}
