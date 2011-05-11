package upserver.resources;

import upinterfaces.UPXMLEvent;
import upinterfaces.UPXMLSimpleMessage;

class Event extends UPResource {

	@Override
	protected UPResponse get(String[] parameters) {
		return new UPResponse(200, new UPXMLSimpleMessage("Teste"));
	}

	@Override
	protected UPResponse post(String[] parameters, String message) {
		UPXMLEvent event = null;
		try {
			event = (UPXMLEvent)xstream.fromXML(message);
		} catch(Exception e) {
			e.printStackTrace();
		}
		return new UPResponse(200, new UPXMLSimpleMessage("Value: " + event.value));
	}
}
