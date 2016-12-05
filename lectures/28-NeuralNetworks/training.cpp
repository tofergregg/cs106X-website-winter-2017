NeuralNet train() {
   // at start neuralNet has "random" weights
	NeuralNet neuralNet = buildGraph();
	Vector<Image> trainData = loadData();

   // repeat many times..
	for(int i = 0; i < ITERS; i++) {
	   // for each image, update weights
	   for(Image img : trainData) {
	      neuralNet.backprop(img);
	   }
	}

	return neuralNet;
}

double test(NeuralNet neuralNet) {
	Vector<Image> testData = loadData();
	double correct = 0;

	// for each image make a prediction
	for(Image img : testData) {
      int prediction = predict(neuralNet, img);
      if(isCorrect(img, prediction)) {
         correct++;
      }
	}
	return correct / testData.size();
}

int main() {
   // learn from data
	NeuralNet neuralNet = train();

	// test your model
	double accuracy = test();
	cout << "Train accuracy: " << accuracy;
}