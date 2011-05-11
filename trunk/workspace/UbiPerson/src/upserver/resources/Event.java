package upserver.resources;

import upinterfaces.UPXMLEvent;
import upinterfaces.UPXMLSimpleMessage;

class Event extends UPResource {

	@Override
	protected UPResponse get(String[] parameters) {
		return new UPResponse(200, new UPXMLSimpleMessage("Teste " + parameters[1]));
	}

	@Override
	protected UPResponse post(String[] parameters, String message) {
		UPXMLEvent event = (UPXMLEvent)xstream.fromXML(message);
		return new UPResponse(200, new UPXMLSimpleMessage("Value: " + event.value));
	}
}
