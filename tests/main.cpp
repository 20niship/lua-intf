#define LUAINTF_LINK_LUA_COMPILED_IN_CXX 0
#include <LuaIntf/LuaIntf.h>
#include <iostream>
#include <string>

class Web {
public:
  // base_url is optional
  Web(const std::string& base_url){
    std::cout << "base_url: " << base_url << std::endl;
    m_url = base_url;
  }
  ~Web() = default;

  static void go_home() { std::cout << " go home" << std::endl; }
  static std::string home_url() { return "http://www.google.com"; }
  static void set_home_url(const std::string& url) { std::cout << " set home url" << std::endl; }

  std::string url() const { return m_url; }
  void set_url(const std::string& url) { m_url = url; }
  std::string resolve_url(const std::string& uri) {
    m_url = "hogehoge";
    return m_url;
  }
  std::string load(const std::string& uri){
    m_url = "hogehoge" + uri;
    return m_url;
  }
  std::string m_url;
};

using namespace LuaIntf;

int main() {
  lua_State* L = luaL_newstate();
  luaL_openlibs(L);
  LuaBinding(L)
    .beginClass<Web>("Web")
    .addConstructor(LUA_ARGS(_opt<std::string>))
    .addStaticProperty("home_url", &Web::home_url, &Web::set_home_url)
    .addStaticFunction("go_home", &Web::go_home)
    .addProperty("url", &Web::url, &Web::set_url)
    .addFunction("resolve_url", &Web::resolve_url)
    .addFunction("load", &Web::load, LUA_ARGS(_opt<std::string>))
    .addStaticFunction("lambda",
                       [] {
                         // you can use C++11 lambda expression here too
                         return "yes";
                       })
    .endClass();
}
