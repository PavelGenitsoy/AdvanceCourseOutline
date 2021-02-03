#include <iostream>
#include <memory>
#include <map> 
#include <string>


/*
	Клиент ссылается на какой-то свой сервер, и сервер имеет какой-то список этих клиентов.
*/


//class Client {
//public:
//	void set_server(std::weak_ptr<Server> sr);
//	bool send(const char* msg, const char* to);
//	bool receive(const char* msg, const char* from) {}
//	bool notify() {}
//private:
//	std::weak_ptr<Server> srv;										// было UB dagling pointer когда не юзали weak_ptr
//};
//
//
//class Server {
//public: 
//	bool send(const char* msg, const char* to, const char* from);
//	bool registration(const char* user, std::weak_ptr<Client> client) {
//		clients[user] = client;
//	}
//	void close(const char* user);
//private:
//	std::map<std::string, std::weak_ptr<Client>> clients;         // было UB dagling pointer когда не юзали weak_ptr
//};
//
//
//void Client::set_server(std::weak_ptr<Server> sr) {
//	srv = sr; 
//}
//
//
//bool Client::send(const char* msg, const char* to) {
//	if(auto server = srv.lock())
//		server->send(msg, "some", "other");
//}
//
//
//void Server::close(const char* user) {  // только когда юзеры будут закрывать, то будет обнулятся. Но можно и забыть закрыть....
//	if (auto сlient = clients[user].lock())
//		сlient = nullptr;
//}
//
//
//bool Server::send(const char* msg, const char* to, const char* from) {
//	Client* clientTo = clients[to];
//	Client* clientFrom = clients[from];
//
//	if (clientTo && clientFrom) {  // еслы не обнулили эти указатели, а по факту уже этих клиентов нет, то будет UB
//		clientTo->receive(msg, from);
//		clientFrom->notify();
//	}
//}


int main(int args, const char* argv) {

	/*std::shared_ptr<Server> srv;

	std::shared_ptr<Client> cl1;
	cl1.set_server(srv);
	srv.registration("other1", &cl1);

	std::shared_ptr<Client> cl2;
	cl2.set_server(&srv);
	srv.registration("other2", &cl2);
*/


	system("pause");
	return 0;
}