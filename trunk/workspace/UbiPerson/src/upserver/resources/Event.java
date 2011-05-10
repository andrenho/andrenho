package upserver.resources;

import upinterfaces.UPXMLSimpleMessage;

class Event extends UPResource {

	@Override
	protected UPResponse get(String[] parameters) {
		return new UPResponse(200, new UPXMLSimpleMessage("Teste ok."));
	}

	
}
