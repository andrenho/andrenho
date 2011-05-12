package upinterfaces;

import com.thoughtworks.xstream.XStream;
import com.thoughtworks.xstream.io.xml.DomDriver;

public class UPXMLManager {

	public static XStream initializeXMLAlias()
	{
		XStream xstream = new XStream(new DomDriver());
		xstream.alias("event", UPXMLEvent.class); // TODO - isto deve ir em outro lugar!
		xstream.alias("events", UPXMLEventList.class);
		xstream.alias("reply", UPXMLSimpleMessage.class);
		xstream.alias("inference", UPXMLInferredData.class);
		return xstream;
	}

}
