function buildNetwork()

	-- The transfer parameters
	local transfer = nn.Linear(self.n_hidden, self.n_hidden)

	-- The first layer 
	local start = nn.Linear(1, self.n_hidden)

	-- Prototypical layer
	local inputM = nn.Identity()(); -- the memory input
	local inputX = nn.Identity()(); -- the last student activity
	local inputY = nn.Identity()(); -- the next question answered
	local truth  = nn.Identity()(); -- whether the next question is correct

	local linM   = transfer:clone('weight', 'bias')(inputM);
	local linX   = nn.Linear(self.n_input, self.n_hidden)(inputX);
	local madd   = nn.CAddTable()({linM, linX});
	local hidden = nn.Tanh()(madd);
	
	local predInput = nil
	if(self.dropoutPred) then
		predInput = nn.Dropout()(hidden)
	else
		predInput = hidden
	end

	local linY = nn.Linear(self.n_hidden, self.n_questions)(predInput);
	local pred_output   = nn.Sigmoid()(linY);
	local pred          = nn.Sum(2)(nn.CMulTable()({pred_output, inputY}));
	local err           = nn.BCECriterion()({pred, truth})

	local network       = nn.gModule({inputM, inputX, inputY, truth}, {pred, err, hidden});

