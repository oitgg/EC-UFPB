#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <mutex>
#include <sstream>
#include <ctime>
 
using namespace std;
mutex m;
class Log {
	ofstream log_file;
	public:
		Log();
		void write(string text);
};

Log::Log() {
	cout << "Inicializando o .log" << endl;
	
	if (freopen("log.txt", "a+", stderr)==NULL) {
		cout << "Erro criando o .log" << endl;
	} 
	
}
void Log::write(string text) {
	
	m.lock();
	cerr << text << endl;
	
	log_file << text << "\n";
	
	m.unlock();
}

string RemoveSub(string& sInput, const string& sub)
{
    string::size_type foundpos = sInput.find(sub);
    if ( foundpos != string::npos )
        sInput.erase(sInput.begin() + foundpos, sInput.begin() + foundpos + sub.length());
 
    return sInput;
}
 
bool Processing(string file, int sd, string type, int* bytes_proc) {
	
  time_t rawtime;
  struct tm * timeinfo;
  char buffer[200];
  
 	string path = "./files/" + file;
 	string line;
 	string content = "";
 	int s = sd;
 	
 	ifstream file_requested(path.c_str());
 	
 	if(file_requested.is_open()) {
 		
 		while (getline(file_requested,line)) {		// Laço que percorre o arquivo requisitado por completo, linha por linha.
		    		content += line + "\n";	
		    		*bytes_proc += line.size();	
		    		
		}
		if (type == "html") {
			
        	
	 		send(s,content.c_str(),content.size(),0);

	 	} else if (type == "txt") {
	 		
	 		send(s,content.c_str(),content.size(),0);
	 	} else if (type == "jpg") {
	 		
	 		send(s,content.c_str(),content.size(),0);
	 	}
 		file_requested.close();
 		return true;
 	} else {
 		cout << "Arquivo nao encontrado" << endl;
 		time (&rawtime);
  		timeinfo = localtime(&rawtime);

  		strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
  		string str_buf(buffer);
  		string resp;
  		cout << "DATE:" << buffer << endl;
 		if (type == "html") {
	 		resp = "<html><head><title>Not Found</title></head><body><b>HTTP/1.1 404 NOT FOUND \n<b/></body></html>\n";
	 		
	 	} else if (type == "txt") {
	 		resp = "<html><head><title>Not Found</title></head><body><b>HTTP/1.1 404 NOT FOUND \n<b/></body></html>\n";
	 		
	 	} else if (type == "jpg") {
	 		resp = "<html><head><title>Not Found</title></head><body><b>HTTP/1.1 404 NOT FOUND \n<b/></body></html>\n";
	 		
	 	}
  		
 		cout << "RESP:" << resp << endl;
 		send(s,resp.c_str(),resp.size(),0);
 		return false;
 	}

 	
   
}
 
void receive_request(int vsd, Log* l, string ip) {

  int udpSocket, nBytes;
  struct sockaddr_in serverAddr, clientAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size, client_addr_size;
  int i;
  string type;
  string client_ip = "Client IP:" + ip;
  cout << "Client IP:" << client_ip << endl;
  string resp;
  char buffer[1024];
  int sd = vsd;
  time_t rawtime;
  struct tm * timeinfo;
  char buffer_resp[200];
  printf("connected %d\n",sd);
  recv(sd, buffer, sizeof(buffer),0);
  int bytes_processed = 0;
 
  if ((buffer[0])!='G' and (buffer[1])!='E' and (buffer[2])!='T') {
  		time_t rawtime;
  		time (&rawtime);
  		struct tm * timeinfo;
  		char buffer2[200];
  		timeinfo = localtime(&rawtime);

  		strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
  		string str_buf(buffer2);
  		string resp;
  		cout << "DATE:" << buffer2 << endl;
        resp = "<html><head><title>Bad Request</title></head>"
        		"<body><b>HTTP/1.1 404 BAD REQUEST \n"
        		"Date: " + str_buf + "\n Server: Elcius Server \n Content-Type: text/html\n Connection: Closed\n\n\n\n<b/></body></html>\n";
        
        cout << "ERRO GET" << endl;
        string resp_log = "HTTP/1.1 400 Bad Request\n"
		        	"Date: " + str_buf + "\n "
		        	"Server: Apache/2.2.14 (Win) \n"
		        	"Content-Type: text/html\n"
		            "Connection: Closed\n";
		l->write(resp_log);
        send(sd,resp.c_str(),resp.size(),0);
    
  } else {
    cout << "GET anexado" << endl;

    printf("recv buffer: %s",buffer);
    string buf(buffer);
    size_t found = buf.find(".ico");
    if (found==string::npos) {
 
    	l->write("---------------- Requisicao");
    	l->write(client_ip);
    	l->write(buf);
    	
    	size_t found_html = buf.find(".html");
 		if (found_html != string::npos)
 			type = "html";
 		size_t found_txt = buf.find(".txt");
 		if (found_txt != string::npos)
 			type = "txt";
 		size_t found_jpg = buf.find(".jpg");
 		if (found_jpg != string::npos)
 			type = "jpg";
        
        size_t pos = buf.find("/");
        string file = buf.substr(pos+1);
        cout << "TYPE:" << type << endl;
        if (type == "html") {
        	cout << "FILE:" << file << endl;
        	time (&rawtime);
	  		timeinfo = localtime(&rawtime);

	  		strftime(buffer_resp,80,"%d-%m-%Y %I:%M:%S",timeinfo);
	  		string str_buf(buffer_resp);
	 		resp = "HTTP/1.1 200 OK \n"
		        	"Date: " + str_buf + "\n"
		        	"Server: Apache/2.2.14 (Win) \n"
		        	"Content-Type: text/html\n"
		            "Connection: Closed\n";
		        	
        
	        size_t pos2 = file.find("l");
	        file.erase(pos2+1, file.size());
	        
	        
	        
	    } else if (type == "txt") {
	    	cout << "FILE:" << file << endl;
        	time (&rawtime);
	  		timeinfo = localtime(&rawtime);

	  		strftime(buffer_resp,80,"%d-%m-%Y %I:%M:%S",timeinfo);
	  		string str_buf(buffer_resp);
	 		resp = "HTTP/1.1 200 OK \n"
		        	"Date: " + str_buf + "\n"
		        	"Server: Apache/2.2.14 (Win) \n"
		        	"Content-Type: text/plain\n"
		            "Connection: Closed\n";
	        size_t pos2 = file.find(" ");
	        file.erase(pos2, file.size());
	        
	        
	        
	    } else if (type == "jpg") {
	    	cout << "FILE:" << file << endl;
        	time (&rawtime);
	  		timeinfo = localtime(&rawtime);

	  		strftime(buffer_resp,80,"%d-%m-%Y %I:%M:%S",timeinfo);
	  		string str_buf(buffer_resp);
	 		resp = "HTTP/1.1 200 OK \n"
		        	"Date: " + str_buf + "\n "
		        	"Server: Apache/2.2.14 (Win) \n"
		        	"Content-Type: image/jpeg\n"
		            "Connection: Closed\n";
	        size_t pos2 = file.find(" ");
	        file.erase(pos2, file.size());
	        
	        
	        
 		}
 		
 		bool status = Processing(file,sd,type, &bytes_processed);
 		if (status == false) {
 			time (&rawtime);
	  		timeinfo = localtime(&rawtime);
	  		string resp_log;
	  		string length_cont=to_string(bytes_processed);
	  		strftime(buffer_resp,80,"%d-%m-%Y %I:%M:%S",timeinfo);
	  		string str_buf(buffer_resp);
 			if (type == "html") {
        	resp_log = "HTTP/1.1 404 Not Found\n"
		        	"Date: " + str_buf + "\n "
		        	"Server: Apache/2.2.14 (Win) \n"
		        	"Content-Length: 0\n"
		        	"Content-Type: text/html\n"
		            "Connection: Closed\n";
	    } else if (type == "txt") {
	    	resp_log = "HTTP/1.1 404 Not Found\n"
		        	"Date: " + str_buf + "\n "
		        	"Server: Apache/2.2.14 (Win) \n"
		        	"Content-Length: 0\n"
		        	"Content-Type: text/plain\n"
		            "Connection: Closed\n";
	        
	    } else if (type == "jpg") {
	    	resp_log = "HTTP/1.1 404 Not Found\n"
		        	"Date: " + str_buf + "\n "
		        	"Server: Apache/2.2.14 (Win) \n"
		        	"Content-Length: 0\n"
		        	"Content-Type: image/jpeg\n"
		            "Connection: Closed\n";

 		}
		l->write(resp_log);
 		} else {
 			time (&rawtime);
	  		timeinfo = localtime(&rawtime);
	  		string resp_log;
	  		strftime(buffer_resp,80,"%d-%m-%Y %I:%M:%S",timeinfo);
	  		string str_buf(buffer_resp);
	  		string length_cont=to_string(bytes_processed);
	  		cout << "BYTES PROCESSED:" << endl;
 			if (type == "html") {
        	resp_log = "HTTP/1.1 200 OK \n"
		        	"Date: " + str_buf + "\n"
		        	"Server: Apache/2.2.14 (Win) \n"
		        	"Content-Length:" + length_cont + "\n"
		        	"Content-Type: text/html\n"
		            "Connection: Closed\n";
	    } else if (type == "txt") {
	    	resp_log = "HTTP/1.1 200 OK \n"
		        	"Date: " + str_buf + "\n"
		        	"Server: Apache/2.2.14 (Win) \n"
		        	"Content-Length:" + length_cont + "\n"
		        	"Content-Type: text/plain\n"
		            "Connection: Closed\n";
	        
	    } else if (type == "jpg") {
	    	resp_log = "HTTP/1.1 200 OK \n"
		        	"Date: " + str_buf + "\n"
		        	"Server: Apache/2.2.14 (Win) \n"
		        	"Content-Length:" + length_cont + "\n"
		        	"Content-Type: image/jpeg\n"
		            "Connection: Closed\n";

 		}
 		l->write(resp_log);

 		}
        
    }

}
  close(sd);
  printf("Conexão encerrada %d\n",sd);
 
}
 
int main(int argc, char** argv) {
    int sd;
    int port=22222;
    struct sockaddr_in addr, client_addr;
    Log l;
 
    if ( argc != 2 )
        printf("usage: %s <portnum>\n...Using default port (%d).\n", argv[0], port);
    else {
        printf("using port: %s\n",argv[1]);
        port = atoi(argv[1]);
    }
    sd = socket(PF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
 
    if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
        printf("error bind");
    if ( listen(sd, 20) != 0 )
        printf("error listen");
 
        int tc = 0;
 
    while (1)
    {  
        char buffer[1024];
 		char client_ip[1024];
 		socklen_t cli_len = sizeof(client_addr);
        int main = accept(sd, 0, 0);
       	inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN); 
        string ip(client_ip);
        thread t (receive_request, main, &l, ip);
        t.join();
    }
 
 
    return 0;
}