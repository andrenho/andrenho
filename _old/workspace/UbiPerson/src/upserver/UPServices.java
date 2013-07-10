package upserver;

import upinterfaces.UPXMLEvent;
import upinterfaces.UPXMLEventList;
import upinterfaces.UPXMLInferredData;

public class UPServices {
	
	public UPXMLEventList events = new UPXMLEventList();
	private UPInferenceCache inferenceCache;

	public UPServices(UPInferenceCache inferenceCache) {
		this.inferenceCache = inferenceCache;
	}

	public void registerEvent(UPXMLEvent event) {
		System.out.println("Novo evento registrado.");
		events.add(event);
	}

	public UPXMLInferredData infer(String user) {
		return this.inferenceCache.infer(user);
	}

}
