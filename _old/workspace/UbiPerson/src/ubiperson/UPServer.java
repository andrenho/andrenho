package ubiperson;

import upserver.UPCommunication;
import upserver.UPInferenceCache;
import upserver.UPInferenceEngine;
import upserver.UPRemoteMethod;
import upserver.UPServices;

public class UPServer {

        public static void main(String[] args) throws Exception
        {
                UPInferenceEngine inferenceEngine = new UPInferenceEngine();
                UPInferenceCache inferenceCache = new UPInferenceCache(inferenceEngine);
                UPServices services = new UPServices(inferenceCache);
                inferenceEngine.database = services.events;
                UPCommunication comm = new UPCommunication(services, 8080);
                UPRemoteMethod remote = new UPRemoteMethod(services);
                comm.run();
        }

}