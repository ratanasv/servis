// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "VISTAS.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <boost/tr1/memory.hpp>
#include <vistas/vistas.h>
#include <SHP3D.h>
#include <Envision.h>
#include <vector>
#include <stdexcept>

#ifdef MACOSX
const VI_String DATA_PREFIX = VI_String("/Users/ratanasv/Documents/data/");
#else
const VI_String DATA_PREFIX = VI_String("/home/ubuntu/data/");
#endif

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using std::tr1::shared_ptr;

using namespace  ::servis;
class VISTASHandler : virtual public VISTASIf {
public:
	VISTASHandler() {
		// Your initialization goes here
	}

	virtual void getTerrain(Terrain& _return, const std::string& fileName) {
		// Your implementation goes here
		printf("getTerrain\n %s", fileName.c_str());
		shared_ptr<SHP3D> shp3dPlugin(new SHP3D());
		shared_ptr<EnvisionDataPlugin> envisionPlugin(new EnvisionDataPlugin());
		const VI_Path pathToShp = VI_Path(DATA_PREFIX + VI_String("eastern_oregon/idu3D.shp"));
		envisionPlugin->Set(pathToShp);
		shp3dPlugin->SetData(envisionPlugin.get(), 0);
		shp3dPlugin->SetAttribute(VI_String("LULC_A"));
		auto shapeMesh = shp3dPlugin->GetMesh();
		auto vertexCount = shapeMesh.GetVertexCount();
		auto indexCount = shapeMesh.GetIndexCount();

		_return.vertices.reserve(vertexCount);
		float* vertexPtr = shapeMesh.AcquireVertexArray();
		for (int i=0; i<vertexCount; i++) {
			double x = (double)vertexPtr[3*i+0];
			double y = (double)vertexPtr[3*i+1];
			double z = (double)vertexPtr[3*i+2];
			_return.vertices.push_back(V3(x,y,z));
		}
		shapeMesh.ReleaseVertexArray();


		_return.indices.reserve(indexCount);
		unsigned* indexPtr = shapeMesh.AcquireIndexArray();
		for (int i=0; i<indexCount; i++) {
			_return.indices.push_back((int32_t) indexPtr[i]);
		}
		shapeMesh.ReleaseIndexArray();
	}

	virtual void getColor(std::vector<V3> & _return, const std::string& fileName, const std::string& attribute) {
		// Your implementation goes here
		printf("getColor\n %s %s", fileName.c_str(), attribute.c_str());
	}

	virtual void getNormalMap(Texture& _return, const std::string& fileName) {
		// Your implementation goes here
		printf("getNormalMap\n %s", fileName.c_str());
	}

	virtual void getTextureMap(Texture& _return, const std::string& fileName, const std::string& attribute) {
		// Your implementation goes here
		printf("getTextureMap\n %s %s", fileName.c_str(), attribute.c_str());
	}

	virtual void getAttributes(std::vector<std::string> & _return, const std::string& fileName) {
		printf("getAttributes %s \n", fileName.c_str());
		shared_ptr<EnvisionDataPlugin> envisionPlugin(new EnvisionDataPlugin());
		const VI_Path pathToShp = VI_Path(DATA_PREFIX + VI_String(fileName));
		envisionPlugin->Set(pathToShp);
		auto attributeList = envisionPlugin->GetAttributes();
		_return.insert(_return.begin(), attributeList.begin(), attributeList.end());
	}

	virtual void getDatasets(std::vector<std::string> & _return) {
		// Your implementation goes here
		printf("getDatasets\n");
	}

};

int main(int argc, char **argv) {
	int port = 9090;
	shared_ptr<VISTASHandler> handler(new VISTASHandler());
	shared_ptr<TProcessor> processor(new VISTASProcessor(handler));
	shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
#ifdef MACOSX
	shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
#else
	shared_ptr<TTransportFactory> transportFactory(new TFramedTransportFactory());
#endif
	shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

	TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
	server.serve();
	return 0;
}

