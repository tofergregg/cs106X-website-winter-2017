if (typeof SpecialEffects == "undefined") {
	"use strict";

	/** DOM class stores things related to manipulating the page through the DOM. */
	function SpecialEffects() {}

	/** Applies a cool animated fade effect to make the given element disappear. */
	SpecialEffects.fade = function(element, delay) {
		if (!delay) {
			delay = 100;
		}
		element.style.opacity = 1.0;

		// show message for 5 sec then disappear
		var timer = 0;
		var fadeFunc = function() {
			// loading.style.visibility = "hidden";
			if (!DOM.fadeTick(element)) {
				clearInterval(timer);
			}
		};

		timer = setInterval(fadeFunc, 100);
	};

	/** Callback that does one frame of animation of the cool animated fade effect. */
	SpecialEffects.fadeTick = function(element) {
		if (element.style.opacity === undefined) {
			element.style.opacity = 0.975;
			return true;
		} else if (element.style.opacity > 0.0) {
			element.style.opacity -= 0.025;
			return true;
		} else {
			// done fading
			element.style.visibility = "hidden";
			element.style.opacity = 1.0;
			return false;
		}
	};

	SpecialEffects.setupClickToShowArea = function(element) {
		var title = element.getAttribute(rel) || "";
		var a = document.createElement("a");
		a.href = "#";
		a.innerHTML = title + " (click to show)";
		a.onclick = function(event) {
			alert("yay");
			event.stopPropagation();
			return false;
		};
		
		var div = document.createElement("div");
		div.appendChild(a);
		
		element.insertBefore(div, element.firstChild);
	};
	
	SpecialEffects.setupClickToShowAreas = function(element) {
		element = element || document.body;
		var clickToShows = element.querySelectorAll(".clicktoshow");
		for (var i = 0; i < clickToShows.length; i++) {
			SpecialEffects.setupClickToShowArea(clickToShows[i]);
		}
	};
}
