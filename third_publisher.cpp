#include <chrono>
#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

using namespace std::chrono_literals;

using std::placeholders::_1;

class ThirdPublisher : public rclcpp::Node
{
public:
  ThirdPublisher()
  : Node("second_publisher")
  {
    publisher = this->create_publisher<example_interfaces::msg::Int64>("number3", 10);

    subscriber = this->create_subscription<example_interfaces::msg::Int64>(
      "number2", 10,
      std::bind(&ThirdPublisher::topic_callback, this, _1));
  }

private:
  void topic_callback(const example_interfaces::msg::Int64::SharedPtr msg)
  {
    valor = msg->data*10;

    auto message = example_interfaces::msg::Int64();
    message.data = valor;

    RCLCPP_INFO(this->get_logger(), "Publishing: %ld", message.data);
    publisher->publish(message);
  }
  
  int64_t valor;

  rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher;
  rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscriber;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ThirdPublisher>());
  rclcpp::shutdown();
  return 0;
}
