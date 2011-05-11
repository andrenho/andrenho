package upserver.resources;

import upinterfaces.UPXML;
import upinterfaces.UPXMLSimpleMessage;

class Event extends UPResource {

	@Override
	protected UPResponse get(String[] parameters) {
		return new UPResponse(200, new UPXMLSimpleMessage("Teste " + parameters[1]));
	}

	@Override
	protected UPResponse post(String[] parameters, UPXML command) {
		return new UPResponse(200, new UPXMLSimpleMessage("Ok."));
	}
}
