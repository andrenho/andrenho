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
		int c = 0;
		for(UPXMLEvent event: database)
			if(event.user.equals(user))
			{
				d += event.value;
				c += 1;
			}
		if(c > 0)
			return new UPXMLInferredData(d / c);
		else
			return new UPXMLInferredData(0.0);
	}

}
