

function importCss() {
   var html = '<link rel="stylesheet" href="karel/css/style.css" type="text/css" />';
   html += '<link rel="stylesheet" href="karel/boxy/stylesheets/boxy.css" type="text/css" />';
   document.write(html);
}

/**
    * Function: Create Image Button
    * -------------
    * Makes a button with an image that lives in src. 
    * Returns the button
    */
   function createImageButton(parent, src, id, tooltip, specialClass) {
      var button = document.createElement('button');
      var buttonImage = document.createElement('img');
      buttonImage.setAttribute('src', src);
      buttonImage.setAttribute('height', 30);
      buttonImage.setAttribute('width', 30);
      button.appendChild(buttonImage);
      button.id = id;
      button.className = 'interactor';
      if(specialClass){
         button.className = specialClass;
      }
      parent.appendChild(button);
      return button;
   }

   /**
    * Create Text Button
    * -------------
    * Makes a button with the given label 
    * Returns the button
    */
   function createTextButton(parent, label, id, btnClass) {
      var button = document.createElement('button');
      button.className = btnClass;
      button.innerHTML = label;
      button.id = id;
      parent.appendChild(button);
      return button;
   }

   function addText(parent, text) {
      parent.innerHTML += text;
   }

   function addSpace(parent) {
      addText(parent, '&nbsp;');
   }
   
   function addWorldDropDown(parent, specialId) {

      var worldSelector = document.createElement('button');
      worldSelector.className = 'btn btn-default dropdown-toggle pull-left interactor';
      worldSelector.setAttribute('type', 'button');
      worldSelector.setAttribute('data-toogle', 'dropdown');

      var html = 'World <span class="caret"></span>'
    /*<ul class="dropdown-menu" role="menu">\
    <li><a href="#">7x7</a></li>\
    <li><a href="#">8x8</a></li>\
    <li><a href="#">9x9</a></li>\
  </ul>';*/
       worldSelector.innerHTML = html;
       parent.appendChild(worldSelector);
      return worldSelector;
   }
   
function importEditor(id, parentId) {
   var code = document.createElement('div');
   code.innerHTML = STARTER_CODE;
   code.id        = id;
   var editorDiv = document.getElementById(parentId);
   editorDiv.appendChild(code); 
   var editor = ace.edit(id);
   editor.setTheme('ace/theme/jeremys');
   var JavaMode = require("ace/mode/java").Mode;
   editor.getSession().setMode(new JavaMode());
   editor.setReadOnly(false);
   // this line turns off automatic error detection
   editor.getSession().setUseWorker(false);
   code.style.fontSize='14px';
   window._editor = editor;
   return editor; 
}

function importButtonBar() {
   var runBar = document.getElementById('runButtonBar');
   createTextButton(runBar, '<span class="glyphicon glyphicon-play"></span> Run Program', 'playButton', 'btn btn-primary interactor');
   //addWorldDropDown(runBar, 'programWorldDrop');
}

function importScripts(list) {
   var html = '';
   for (var i = 0; i < list.length; i++) {
      html += list[i];
   }
   document.write(html);
}

function importJsLibraries() {
   var scripts = [
      '<script src="karel/lib/jquery.js"></script>',
      '<script src="karel/lib/browser_detect.js"></script>',
      '<script src="karel/lib/util.js"></script>',
      '<script src="karel/lib/tabs.js"></script>',
      '<script src="karel/codeMirror/js/codemirror.js"></script>',
      '<script src="karel/ace/ace-uncompressed.js"></script>',
      '<script src="karel/ace/theme-jeremys.js"></script>',
      '<script src="karel/ace/mode-javascript.js"></script>',
      '<script src="karel/ace/mode-java.js"></script>',
      '<script src="karel/lib/curvycorners.js"></script>',
	  '<script src="karel/lib/jquery.js"></script>',
      //'<script src="http://cdn.jquerytools.org/1.2.5/jquery.tools.min.js"></script>',
      '<script src="karel/boxy/jquery.boxy.js"></script>',
   ]
   importScripts(scripts);
}


function importKarelIde() {
   var scripts = [
		'<script src="karel/js/ide/karelImages.js"></script>',
		'<script src="karel/js/ide/karelSingleton.js"></script>',
		'<script src="karel/js/ide/karelConstants.js"></script>',
		'<script src="karel/js/ide/action.js"></script>',
		'<script src="karel/js/ide/beepers.js"></script>',
		'<script src="karel/js/ide/walls.js"></script>',
		'<script src="karel/js/ide/squareColors.js"></script>',
		'<script src="karel/js/ide/canvasModel.js"></script>',
		'<script src="karel/js/ide/karelModel.js"></script>',
		'<script src="karel/js/ide/karelView.js"></script>',
		'<script src="karel/js/ide/karel.js"></script>',
		'<script src="karel/js/ide/karelCompiledEngine.js"></script>',
		'<script src="karel/js/ide/karelEvalEngine.js"></script>',
		'<script src="karel/js/ide/karelIde.js"></script>',
		'<script src="karel/js/html/starterCode.js"></script>',
		'<!--<script src="karel/js/ide/mainIdeController.js"></script>-->',
	]
	importScripts(scripts);
		
}

function importCompiler() {
   var scripts = [ 
      '<script src="karel/js/compiler/karelCompiler.js"></script>',
      '<script src="karel/js/compiler/scanner/TokenScanner.js"></script>',
      '<script src="karel/js/compiler/parser/Parser.js"></script>',
      '<script src="karel/js/compiler/parser/XParser.js"></script>',
      '<script src="karel/js/compiler/vm/VM.js"></script>',
      '<script src="karel/js/compiler/vm/XVM.js"></script>',
      '<script src="karel/js/compiler/karel/KarelParser.js"></script>',
      '<script src="karel/js/compiler/karel/KarelVM.js"></script>'
   ]
   importScripts(scripts);	
}

function importLearnEngine() {
   var scripts = [

		'<script src="karel/js/learn/makeAbsoluteDiv.js"></script>',
		'<script src="karel/js/learn/unitProgress.js"></script>',
		'<script src="karel/js/learn/progressModel.js"></script>',
		'<script src="karel/js/learn/lessonsModel.js"></script>',
		'<script src="karel/js/learn/homeScreen.js"></script>',
		'<script src="karel/js/learn/textElement.js"></script>',
		'<script src="karel/js/learn/textButton.js"></script>',
		'<script src="karel/js/learn/unitBox.js"></script>',
		'<script src="karel/js/learn/imageElement.js"></script>',
		'<script src="karel/js/learn/unitTestElement.js"></script>',
		'<script src="karel/js/learn/textBox.js"></script>',
		'<script src="karel/js/learn/videoElement.js"></script>',
		'<script src="karel/js/learn/karelCommandButton.js"></script>',
		'<script src="karel/js/learn/karelEditorElement.js"></script>',
		'<script src="karel/js/learn/karelStaticCanvasElement.js"></script>',
		'<script src="karel/js/learn/karelCanvasElement.js"></script>',
		'<script src="karel/js/learn/karelIdeMessage.js"></script>',
		'<script src="karel/js/learn/karelIdeButtons.js"></script>',
		'<script src="karel/js/learn/karelIdeElement.js"></script>',
		'<script src="karel/js/learn/programElement.js"></script>',
		'<script src="karel/js/learn/imageButton.js"></script>',
		'<script src="karel/js/learn/content.js"></script>',
		'<script src="karel/js/learn/centerArea.js"></script>',
		'<script src="karel/js/learn/titleElement.js"></script>',
		'<script src="karel/js/learn/header.js"></script>',
		'<script src="karel/js/learn/progressBox.js"></script>',
		'<script src="karel/js/learn/progressBar.js"></script>',
		'<script src="karel/js/learn/karelLearnEngine.js"></script>',
	]
	importScripts(scripts);	
}

function importController() {
   var scripts = [
		'<script src="karel/js/server/server.js"></script>',
	]
	importScripts(scripts);
}

function importReference() {
   var scripts = [
		'<script src="karel/js/dialog/referenceDialog.js"></script>',
		'<script src="karel/js/dialog/deployDialog.js"></script>',
	]
	importScripts(scripts);	
}

function importJs() {
   importJsLibraries();
   importController();
   importCompiler();
   importKarelIde();
   importLearnEngine();
   importReference();
}
