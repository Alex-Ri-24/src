#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"
  
#include <memory>

void add(const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
          std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response)
{
  // SOMA
  response->sum = request->a + request->b;
  // Pedido de soma
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\na: %ld" " b: %ld",
                request->a, request->b);
  // Envio da resposta
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld]", (long int)response->sum);
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_ints_server");

  rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr service =
    node->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints", &add);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add two ints.");

  rclcpp::spin(node);
  rclcpp::shutdown();
}
// Código para somar três inteiros, usando mensagem customizadas feitas no msg e srv 

// #include "rclcpp/rclcpp.hpp"
// #include "package/srv/add_three_ints.hpp"                                        // CHANGE

// #include <memory>

// void add(const std::shared_ptr<package::srv::AddThreeInts::Request> request,     // CHANGE
//           std::shared_ptr<package::srv::AddThreeInts::Response>       response)  // CHANGE
// {
//   response->sum = request->a + request->b + request->c;                                      // CHANGE
//   RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\na: %ld" " b: %ld" " c: %ld",  // CHANGE
//                 request->a, request->b, request->c);                                         // CHANGE
//   RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld]", (long int)response->sum);
// }

// int main(int argc, char **argv)
// {
//   rclcpp::init(argc, argv);

//   std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_three_ints_server");   // CHANGE

//   rclcpp::Service<package::srv::AddThreeInts>::SharedPtr service =               // CHANGE
//     node->create_service<package::srv::AddThreeInts>("add_three_ints",  &add);   // CHANGE

//   RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add three ints.");                     // CHANGE

//   rclcpp::spin(node);
//   rclcpp::shutdown();
// }
