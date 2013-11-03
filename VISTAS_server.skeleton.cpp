// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "VISTAS.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/concurrency/ThreadManager.h>
#include <boost/tr1/memory.hpp>
#include "vistasServer.h"

#include <vector>
#include <stdexcept>
#include <algorithm>




using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using apache::thrift::concurrency::PosixThreadFactory;

using std::runtime_error;
using namespace  ::servis;

const int NUM_THREADS = 4;


class VISTASHandler : virtual public VISTASIf {
public:
	virtual void getTerrain(Terrain& _return, const std::string& folderName) {
		printf("getTerrain %s \n", folderName.c_str());
		auto shapeMesh = getMesh(folderName);

		auto vertexCount = shapeMesh.GetVertexCount();
		auto indexCount = shapeMesh.GetIndexCount();

		_return.vertices.reserve(vertexCount);
		_return.indices.reserve(indexCount);

		float* vertexPtr = shapeMesh.AcquireVertexArray();
		for (int i=0; i<vertexCount; i++) {
			double x = (double)vertexPtr[3*i+0];
			double y = (double)vertexPtr[3*i+1];
			double z = (double)vertexPtr[3*i+2];
			_return.vertices.push_back(V3(x,y,z));
		}
		shapeMesh.ReleaseVertexArray();

		unsigned* indexPtr = shapeMesh.AcquireIndexArray(); 
		for (int i=0; i<indexCount; i++) {
			_return.indices.push_back((int)indexPtr[i]);
		}
	}

	virtual void getColor(std::vector<V3> & _return, const std::string& folderName, const std::string& attribute) {
		printf("getColor %s %s \n", folderName.c_str(), attribute.c_str());
		
		auto shapeMesh = getMesh(folderName, attribute);
		
		auto vertexCount = shapeMesh.GetVertexCount();

		_return.reserve(vertexCount);
		float* colorPtr = shapeMesh.AcquireColorArray();
		for (int i=0; i<vertexCount; i++) {
			double x = (double)colorPtr[3*i+0];
			double y = (double)colorPtr[3*i+1];
			double z = (double)colorPtr[3*i+2];
			_return.push_back(V3(x,y,z));
		}
		shapeMesh.ReleaseColorArray();

	}

	virtual void getNormalMap(Texture& _return, const std::string& fileName) {
		// Your implementation goes here
		printf("getNormalMap\n %s", fileName.c_str());
	}

	virtual void getTextureMap(Texture& _return, const std::string& fileName, const std::string& attribute) {
		// Your implementation goes here
		printf("getTextureMap\n %s %s", fileName.c_str(), attribute.c_str());
	}

	virtual void getAttributes(std::vector<std::string> & _return, const std::string& folderName) {
		printf("getAttributes %s \n", folderName.c_str());
		auto dataPlugin = initDataPlugin(folderName);
		auto attributeList = dataPlugin->GetAttributes();
		_return.insert(_return.begin(), attributeList.begin(), attributeList.end());
	}

	virtual void getDatasets(std::vector<std::string> & _return) {
		printf("getDatasets\n");
		VI_Path datasetsRoot(getDataRoot());
		auto datasetsList = datasetsRoot.GetFiles();
		for (auto it : datasetsList) {
			_return.push_back(it.GetElement(-1).c_str());
		}
	}

};

int main(int argc, char **argv) {
	int port = 9090;
	shared_ptr<VISTASHandler> handler(new VISTASHandler());
	shared_ptr<TProcessor> processor(new VISTASProcessor(handler));
	shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
	shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
	shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

	shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(NUM_THREADS);
	shared_ptr<PosixThreadFactory> threadFactory(new PosixThreadFactory());
	threadManager->threadFactory(threadFactory);
	threadManager->start();
	TThreadPoolServer server(processor, serverTransport, transportFactory, protocolFactory, threadManager);
	server.serve();
	return 0;
}

