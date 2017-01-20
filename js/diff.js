/**
 * Marty Stepp's output comparison tool script
 * Recent changes:
 * 15sp: module pattern for better encapsulation; removed dependency on Prototype JS library
 * 14au: better try/catch handling for Ajax requests, better error messages
 */ 

(function() {
	// special value that means this program has graphical output
	var GRAPHICAL_VALUE = "_graphical";
	var OTHER_VALUE = "_other";
	var JUNIT_VALUE = "_junit";

	var codebase = "";
	var timer = null;
	
	var $ = function(id) {
		return document.getElementById(id);
	};

	window.addEventListener("load", function() {
		// ensure that site is viewed using HTTPS
		if (!location.hostname.match(/localhost/) && !location.protocol.match(/https/i)) {
			location.protocol = "https:";
			return;
		}

		$("homework").onchange = homeworkChange;
		$("add").onclick = addClick;
		$("remove").onclick = removeClick;
		$("compare").onclick = compareClick;

		$("expectedtext").spellcheck = false;
		$("expectedtext").onmouseup = textMouseUp;
		$("expectedtext").onclick = textMouseUp;
		$("expectedtext").onkeydown = textMouseUp;
		$("expectedtext").onkeyup = textMouseUp;

		$("actualtext").spellcheck = false;
		$("actualtext").onmouseup = textMouseUp;
		$("actualtext").onclick = textMouseUp;
		$("actualtext").onkeydown = textMouseUp;
		$("actualtext").onkeyup = textMouseUp;
	});

	function textMouseUp(event) {
		var selectionLength = 0;
		if (this.selectionEnd !== undefined &&
				this.selectionStart !== undefined) {
			selectionLength = Math.abs(this.selectionEnd - this.selectionStart);
		} else {
			selectionLength = getSelectedText().length;
		}
		if (selectionLength !== undefined && !isNaN(selectionLength)) {
			$(this.className + "chars").innerHTML = "(" + selectionLength + " characters selected)";
		}
	}


	function numDigits(array) {
		// capped at 9999 lines
		if (array.length >= 1000) {
			return 4;
		} else if (array.length >= 100) {
			return 3;
		} else if (array.length >= 10) {
			return 2;
		}
		return 1;
	}

	function addLineNumbers(text) {
		var lines = text.split(/\n/);
		var digits = numDigits(lines);

		// build new string of lines with prepended numbers
		var newText = "";
		for (var i = 0; i < lines.length; i++) {
			if (newText.length > 0) {
				newText += "\n";
			}

			// don't include a number for a final blank line
			if (i < lines.length - 1 || lines[i].length > 0) {
				newText += padL("" + (i + 1), digits) + "  " + lines[i];
			}
		}

		return newText;
	}

	function hasLineNumbers(text) {
		var lines = text.split(/\n/);
		var alreadyNumberedCount = 0;
		for (var i = 0; i < lines.length; i++) {
			if (lines[i].indexOf("" + (i + 1)) >= 0) {
				alreadyNumberedCount++;
			}
		}

		return alreadyNumberedCount >= lines.length - 1;
	}

	// pre: all lines have numbers
	function removeLineNumbers(text) {
		var lines = text.split(/\n/);
		var digits = numDigits(lines);

		// build new string of lines with prepended numbers
		var newText = "";
		for (var i = 0; i < lines.length; i++) {
			if (newText.length > 0) {
				newText += "\n";
			}
			newText += lines[i].substring(digits + 2);
		}

		return newText;
	}

	function addLineNumbersExpected() {
		if (!hasLineNumbers($("expectedtext").value)) {
			$("expectedtext").value = addLineNumbers(rtrim($("expectedtext").value));
		}
	}

	function addLineNumbersActual() {
		if (!hasLineNumbers($("actualtext").value)) {
			$("actualtext").value = addLineNumbers(rtrim($("actualtext").value));
		}
	}

	function addClick() {
		addLineNumbersExpected();
		addLineNumbersActual();
		compareClick();
	}

	function removeLineNumbersExpected() {
		if (hasLineNumbers($("expectedtext").value)) {
			$("expectedtext").value = removeLineNumbers($("expectedtext").value);
		}
	}

	function removeLineNumbersActual() {
		if (hasLineNumbers($("actualtext").value)) {
			$("actualtext").value = removeLineNumbers($("actualtext").value);
		}
	}

	function removeClick() {
		removeLineNumbersExpected();
		removeLineNumbersActual();
		compareClick();
	}

	function splitIntoLines(text, ignoreLeadingSpaces) {
		// split into lines (trims trailing whitespace, except on POS IE6)
		var lines = text.split(/[ ]*\n/);


		// trim trailing whitespace
		for (var i = 0; i < lines.length; i++) {
			lines[i] = rtrim(lines[i]);

			// possibly also trim leading whitespace
			if (ignoreLeadingSpaces) {
				lines[i] = ltrim(lines[i]);
			}
		}

		return lines;
	}

	function compareClick() {
		if ($("fetchiframe")) {
			$("fetchiframe").blindUp();
		}

		var expectedText = rtrim($("expectedtext").value);
		var actualText = rtrim($("actualtext").value);
		var resultText = "";
		var SEP = "<br />";
		var diffCount = 0;

		var ignoreLeadingSpaces = $("stripwhitespace").checked;
		var expectedLines = splitIntoLines(expectedText, ignoreLeadingSpaces);
		var actualLines = splitIntoLines(actualText, ignoreLeadingSpaces);
		var hasNumbers = hasLineNumbers(expectedText) && hasLineNumbers(actualText);

		var out = betterDiff(expectedLines, actualLines, hasNumbers);
		for (var i = 0; i < out.length; i++) {
	/*
			// I was trying to make the tool understand how to eliminate
			// leading/trailing diffs for creative output,
			// but this JavaScript diff tool doesn't give me back line numbers
			// so it's pretty much impossible to tell "where" a diff is.
			// Screw it.
			if (i == 0 && $("creativestart").checked) {
				// file2 is allowed to have stuff not present in file1
				alert("creative start!");
			} else if (i == out.length - 1 && $("creativeend").checked) {
				// file2 is allowed to have stuff not present in file1
				alert("creative start!");
			}
	*/

			var empty = true;
			if (out[i]["file1"]) {
				for (var j = 0; j < out[i]["file1"].length; j++) {
					empty = false;
					var encoded = htmlEncode(out[i]["file1"][j]);
					resultText += "<del class=\"diff\">" + "&lt; " + encoded + "</del>" + SEP;
					diffCount++;
				}
			}
			if (out[i]["file2"]) {
				for (var j = 0; j < out[i]["file2"].length; j++) {
					empty = false;
					var encoded = htmlEncode(out[i]["file2"][j]);
					resultText += "<ins class=\"diff\">" + "&gt; " + encoded + "</ins>" + SEP;
					diffCount++;
				}
			}

			if (!empty) {
				resultText += SEP;
			}
		}

		if (diffCount > 0) {
			$("differencesheader").innerHTML = "Differences:";
		} else {
			$("differencesheader").innerHTML = "No differences found.";
		}

		$("result").innerHTML = resultText;
		try {
			if ($("diffarea").style.display == "none") {
				$("diffarea").appear();
			} else {
				$("diffarea").highlight();
			}
		} catch (e) {
			appearHelper($("diffarea"));
		}
	}

	function appearHelper(element, displayType) {
		element.style.display = displayType ? displayType : "block";
		element.style.visibility = "visible";
		element.style.opacity = "1.0";
	}

	function hideHelper(element) {
		element.style.display = "none";
	}

	function homeworkChange(event) {
		if (!this.value) {
			$("expectedtext").value = "";
			return;
		}
		var selected = this.options[this.selectedIndex];
		if (!selected) {
			return;
		}
		var styles = window.getComputedStyle(selected);
		if (styles && styles.visibility == "hidden" || styles.display == "none") {
			event.preventDefault();
			event.stopPropagation();
			this.selectedIndex = 0;
			return false;
		}
		
		if (this.value == GRAPHICAL_VALUE) {
			alert("This assignment uses graphical output, and this Output Comparison Tool is only for comparing text.\n" +
					"You will have to compare graphical output manually by looking at screenshots and comparing them to your program's appearance.");
			return;
		} else if (this.value == OTHER_VALUE) {
			alert("This assignment doesn't produce output that can be compared by this tool.");
			return;
		} else if (this.value == JUNIT_VALUE) {
			alert("This assignment's tests are JUnit programs; run JUnit from Eclipse or jGRASP to verify your program.");
			return;
		}

		/*
		var optgroup = $(this.options[this.selectedIndex]).up("optgroup");
		$("creativestart").checked = optgroup && optgroup.classList.contains("creativestart");
		$("creativeend").checked = optgroup && optgroup.classList.contains("creativeend");
		*/

		if (this.classList.contains("useiframe") ||
				(this.value && this.value.indexOf("http") == 0 && this.value.indexOf("://") >= 0)) {
			// special case: a full URL path name.
			// Can't fetch with Ajax because of security restrictions.
			// The closest we can come is to inject it into an iframe and let the user
			// copy/paste it above.
			$("expectedtext").value = "Because of security restrictions imposed\n" +
					"by the web browser, you have to copy the text\n" +
					"from the white box below into the green box above.\n" +
					"Then you can run the Compare command as usual.\n" +
					"Sorry for the inconvenience.";

			var iframe = document.createElement("iframe");
			iframe.id = "fetchiframe";
			iframe.className = "fetchiframe";
			iframe.src = this.value;
			iframe.style.display = "none";
			$("expectedtext").parentNode.insertBefore(iframe, $("expectedtext").nextSibling ? $("expectedtext").nextSibling : $("expectedtext"));
			//iframe.blindDown();
			iframe.style.display = "";
		} else {
			// standard case; just fetch the file from the web site using Ajax
			if ($("fetchiframe")) {
				// $("fetchiframe").blindUp();
				iframe.style.display = "none";
			}

			//try {
			//    $("loading").appear();
			//} catch (e) {
				appearHelper($("loading"), "inline");
			//}
			$("expectedtext").value = "Downloading..."

			var url = codebase + this.value + "?nocache=" + parseInt(Math.random() * 999999999);
			try {
				var ajax = new XMLHttpRequest();
				ajax.onload = ajaxSuccess;
				ajax.onerror = ajaxError;
				ajax.open("GET", url, true);
				ajax.send();
			} catch (e) {
				ajaxError(null, e);
			}
		}
	}

	// Fetches data using Ajax and calls the given function when it arrives.
	function ajaxSuccess(event) {
		if (this.status == 200) {   // 200 means request succeeded
			// got the data correctly; put it onto the page
			$("expectedtext").value = this.responseText;
			hideHelper($("loading"));
		} else {
			ajaxError(this);
		}
	}
	
	function ajaxError(ajax, exception) {
		hideHelper($("loading"));
		var errorText = "Error making web request.\n\nServer status:\n" +
			  (ajax ? ajax.status : "null") + " " + (ajax ? ajax.statusText : "null") + "\n\n" +
			  "Server response text:\n" + (ajax ? ajax.responseText : "null");
		if (exception) {
			errorText += "\nException: " + exception.message;
		}
		alert(errorText);
		return errorText;
	}

	// A cross-browser way to get the text that is currently selected.
	function getSelectedText() {
		var w=window,d=document,gS='getSelection';
		return (''+(w[gS]?w[gS]():d[gS]?d[gS]():d.selection.createRange().text));
	}

	function htmlEncode(text) {
		text = text.replace(/</g, "&lt;");
		text = text.replace(/>/g, "&gt;");
		text = text.replace(/ /g, "&nbsp;");
		return text;
	}

	function ltrim(str) {
		for (var k = 0; k < str.length && str.charAt(k) <= " "; k++);
		return str.substring(k, str.length);
	}

	function rtrim(str) {
		for (var j = str.length - 1; j >= 0 && str.charAt(j) <= " "; j--);
		return str.substring(0, j+1);
	}

	function trim(str) {
		return ltrim(rtrim(str));
	}

	function padL(text, length) {
		while (text.length < length) {
			text = " " + text;
		}
		return text;
	}


	/* Copyright (c) 2006 Tony Garnock-Jones <tonyg@lshift.net>
	 * Copyright (c) 2006 LShift Ltd. <query@lshift.net>
	 *
	 * Permission is hereby granted, free of charge, to any person
	 * obtaining a copy of this software and associated documentation files
	 * (the "Software"), to deal in the Software without restriction,
	 * including without limitation the rights to use, copy, modify, merge,
	 * publish, distribute, sublicense, and/or sell copies of the Software,
	 * and to permit persons to whom the Software is furnished to do so,
	 * subject to the following conditions:
	 *
	 * The above copyright notice and this permission notice shall be
	 * included in all copies or substantial portions of the Software.
	 *
	 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
	 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
	 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
	 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	 * SOFTWARE.

	 As an example, the output from

	 diff("the quick brown fox jumped over".split(/\s+/),
		  "the quick fox jumps over".split(/\s+/))

	 is

	 [{common:["the","quick"]},
	  {file1:["brown"], file2:[]},
	  {common:["fox"]},
	  {file1:["jumped"], file2:["jumps"]},
	  {common:["over"]}
	 ]

	 */
	function betterDiff(file1, file2, hasNumbers) {
		/* Text diff algorithm following Hunt and McIlroy 1976.
		 * J. W. Hunt and M. D. McIlroy, An algorithm for differential file
		 * comparison, Bell Telephone Laboratories CSTR #41 (1976)
		 * http://www.cs.dartmouth.edu/~doug/
		 *
		 * Expects two arrays of strings.
		 */

		// used to delete line numbers from the starts of lines
		var start1 = 0;
		var start2 = 0;
		if (hasNumbers) {
			start1 = numDigits(file1) + 2;
			start2 = numDigits(file2) + 2;
		}

		var equivalenceClasses = {};
		for (var j = 0; j < file2.length; j++) {
			var line = file2[j];
			if (equivalenceClasses[line.substring(start2)]) {
				equivalenceClasses[line.substring(start2)].push(j);
			} else {
				equivalenceClasses[line.substring(start2)] = [j];
			}
		}

		var candidates = [{file1index: -1,
						   file2index: -1,
						   chain: null}];

		for (var i = 0; i < file1.length; i++) {
			var line = file1[i];
			var file2indices = equivalenceClasses[line.substring(start1)] || [];

			var r = 0;
			var c = candidates[0];

			for (var jX = 0; jX < file2indices.length; jX++) {
				var j = file2indices[jX];

				for (var s = 0; s < candidates.length; s++) {
					if ((candidates[s].file2index < j) &&
						((s == candidates.length - 1) ||
						 (candidates[s + 1].file2index > j)))
						break;
				}

				if (s < candidates.length) {
					var newCandidate = {file1index: i,
										file2index: j,
										chain: candidates[s]};
					if (r == candidates.length) {
						candidates.push(c);
					} else {
						candidates[r] = c;
					}
					r = s + 1;
					c = newCandidate;
					if (r == candidates.length) {
						break; // no point in examining further (j)s
					}
				}
			}

			candidates[r] = c;
		}

		// At this point, we know the LCS: it's in the reverse of the
		// linked-list through .chain of
		// candidates[candidates.length - 1].

		// We now apply the LCS to build a "comm"-style picture of the
		// differences between file1 and file2.

		var result = [];
		var tail1 = file1.length;
		var tail2 = file2.length;
		var common = {common: []};

		function processCommon() {
			if (common.common.length) {
				common.common.reverse();
				result.push(common);
				common = {common: []};
			}
		}

		for (var candidate = candidates[candidates.length - 1];
			 candidate != null;
			 candidate = candidate.chain) {
			var different = {file1: [], file2: []};

			while (--tail1 > candidate.file1index) {
				different.file1.push(file1[tail1]);
			}

			while (--tail2 > candidate.file2index) {
				different.file2.push(file2[tail2]);
			}

			if (different.file1.length || different.file2.length) {
				processCommon();
				different.file1.reverse();
				different.file2.reverse();
				result.push(different);
			}

			if (tail1 >= 0) {
				common.common.push(file1[tail1].substring(start1));
			}
		}

		processCommon();

		result.reverse();
		return result;
	}
})();
