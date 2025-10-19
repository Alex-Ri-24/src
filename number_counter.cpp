#include <chrono>
#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

using std::placeholders::_1;

class NumberCounter : public rclcpp::Node
{
public:
  NumberCounter()
  : Node("number_counter"), counter_(0)
  {
    publisher_ = this->create_publisher<example_interfaces::msg::Int64>("number_count", 10);

    subscriber_ = this->create_subscription<example_interfaces::msg::Int64>(
      "number", 10,
      std::bind(&NumberCounter::topic_callback, this, _1));
  }

private:
  void topic_callback(const example_interfaces::msg::Int64::SharedPtr msg)
  {
    RCLCPP_INFO(this->get_logger(), "Received: %ld", msg->data);

    counter_ += msg->data;

    auto message = example_interfaces::msg::Int64();
    message.data = counter_;
    RCLCPP_INFO(this->get_logger(), "Publishing counter: %ld", message.data);
    publisher_->publish(message);
  }

  int64_t counter_;
  rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
  rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscriber_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<NumberCounter>());
  rclcpp::shutdown();
  return 0;
}