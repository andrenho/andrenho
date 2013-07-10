package upserver;

import upinterfaces.UPXMLInferredData;

public class UPInferenceCache {
	
	private UPInferenceEngine inferenceEngine;

	public UPInferenceCache(UPInferenceEngine inferenceEngine) {
		this.inferenceEngine = inferenceEngine;
	}

	public UPXMLInferredData infer(String user) {
		return inferenceEngine.infer(user);
	}

}
