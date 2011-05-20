package upserver.resources;

import upinterfaces.InvalidXMLException;
import upinterfaces.UPXMLEvent;
import upinterfaces.UPXMLSimpleMessage;

class Event extends UPResource {

	@Override
	protected UPResponse get(String[] parameters) {
		if(parameters.length == 0)
		{
			return new UPResponse(200, services.events);
		}
		else if(parameters.length == 1)
		{
			int n = Integer.parseInt(parameters[0]);
			if(n > services.events.size() || n < 0)
				return new UPResponse(405, new UPXMLSimpleMessage("Invalid parameter."));
			return new UPResponse(200, services.events.get(n));
		}
		else
			return new UPResponse(405, new UPXMLSimpleMessage("Invalid parameter.")); // TODO - verificar código
	}

	@Override
	protected UPResponse post(String[] parameters, String message) throws InvalidXMLException {
		UPXMLEvent event = null;
		try {
			event = (UPXMLEvent)xstream.fromXML(message);
		} catch(Exception e) {
			throw new InvalidXMLException(e);
		}
		System.out.println("Evento recebido! Usuário " + event.user + " realizou o evento \"" + 
				event.action + "\" no contexto " + event.context + " em " + event.date + "."); 
		services.registerEvent(event);
		return new UPResponse(200, new UPXMLSimpleMessage("Event registered."));
	}
}
