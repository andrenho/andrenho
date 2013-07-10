package upserver.resources;

import upinterfaces.UPXMLSimpleMessage;

public class Inference extends UPResource {

	@Override
	protected UPResponse get(String[] parameters) {
		if(parameters.length != 1)
			return new UPResponse(405, new UPXMLSimpleMessage("Invalid parameter."));
		else
			return new UPResponse(200, services.infer(parameters[0]));
	}

}
