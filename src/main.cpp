#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/network/Server.hpp"
#include "oatpp/web/server/HttpRouter.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/protocol/http/outgoing/Response.hpp"
#include "oatpp/web/protocol/http/incoming/Request.hpp"
#include "oatpp/Environment.hpp"
#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/web/server/HttpRequestHandler.hpp"
 
#define O_UNUSED(x) (void)x;

// 自定义请求处理程序
class HelloHandler : public oatpp::web::server::HttpRequestHandler {
public:
    // 处理传入的请求，并返回响应
    std::shared_ptr<oatpp::web::protocol::http::outgoing::Response> handle(
        const std::shared_ptr<oatpp::web::protocol::http::incoming::Request>& request) override {
        O_UNUSED(request); // 忽略请求参数
        return ResponseFactory::createResponse(Status::CODE_200, "Hello World!");
    }
};

int main() {
    oatpp::Environment::init(); // 初始化 Oat++ 环境

    // 创建 TCP 连接提供者，监听端口 8000
    auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared({"0.0.0.0", 8000});

    // 创建 HTTP 路由器
    auto router = oatpp::web::server::HttpRouter::createShared();

    // 注册处理程序到路由器
    router->route("GET", "/hello", std::make_shared<HelloHandler>());

    // 创建 HTTP 连接处理器
    auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);

    // 创建并启动服务器
    oatpp::network::Server server(connectionProvider, connectionHandler);
    //OATPP_LOGd("Server", "Running on port %s", connectionProvider->getProperty("port").toString()->c_str());
    OATPP_LOGd("Server", "Running on port 8000");
    server.run(); // 运行服务器

    // 销毁 Oat++ 环境
    oatpp::Environment::destroy();

    return 0;
}

