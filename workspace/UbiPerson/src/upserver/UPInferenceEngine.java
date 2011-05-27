package upserver;

import upinterfaces.UPXMLEvent;
import upinterfaces.UPXMLEventList;
import upinterfaces.UPXMLInferredData;

public class UPInferenceEngine extends UPInferenceCache {

	public UPXMLEventList database = null;

	public UPInferenceEngine() {
		super(null);
	}
	
	public UPXMLInferredData infer(String user) {
		assert(database != null);
		double d = 0.0;
		for(UPXMLEvent event: database)
			if(event.user.equals(user))
				d += 1;
		return new UPXMLInferredData(d);
	}

}
