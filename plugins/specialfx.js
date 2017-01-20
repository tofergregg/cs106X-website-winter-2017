if (typeof SpecialEffects == "undefined" || !SpecialEffects.isLoaded) {
	"use strict";

	/** DOM class stores things related to manipulating the page through the DOM. */
	var SpecialEffects = function() {};
	SpecialEffects.isLoaded = true;

	/** Applies a cool animated fade effect to make the given element disappear. */
	SpecialEffects.fadeIn = function(element, delay) {
		SpecialEffects.fadeHelper(element, delay, 0.025);
	};
	
	SpecialEffects.fadeOut = function(element, delay) {
		SpecialEffects.fadeHelper(element, delay, -0.025);
	}
	
	SpecialEffects.fadeHelper = function(element, delay, delta) {
		if (!delay) {
			delay = 100;
		}
		element.style.opacity = (delta > 0) ? 0.001 : 0.999;
		element.style.display = "";

		element.__timer = 0;
		var fadeFunc = function() {
			// loading.style.visibility = "hidden";
			if (!SpecialEffects.fadeTick(element, delta)) {
				clearInterval(element.__timer);
				element.__timer = 0;
			}
		};

		element.__timer = setInterval(fadeFunc, delay);
	};

	/** Callback that does one frame of animation of the cool animated fade effect. */
	SpecialEffects.fadeTick = function(element, delta) {
		var opacity = element.style.opacity;
		if (opacity === undefined) {
			opacity = element.style.opacity = (delta < 0) ? 0.999 : 0.001;
			return true;
		}
		
		opacity = parseFloat(opacity);
		// console.log("opacity = " + opacity);
		
		if (0.0 < opacity && opacity < 1.0) {
			opacity += delta;
			element.style.opacity = opacity;
			return true;
		} else {
			// done fading
			element.style.opacity = 1.0;
			if (delta > 0) {
			} else {
				// element.style.visibility = "hidden";
				element.style.display = "none";
			}
			return false;
		}
	};

	SpecialEffects.setupClickToShowArea = function(element) {
		var title = element.getAttribute("rel") || "";
		var a = document.createElement("a");
		a.href = "#";
		a.innerHTML = "<strong>" + title + "</strong> (click to show)";
		a.onclick = function(event) {
			a.parentNode.removeChild(a);
			SpecialEffects.fadeIn(element, 25);
			event.stopPropagation();
			return false;
		};
		
		var div = document.createElement("div");
		div.appendChild(a);
		var parent = element.parentNode;
		parent.insertBefore(div, element);
		element.style.display = "none";
		div.appendChild(element);
	};
	
	SpecialEffects.setupClickToShowAreas = function(element) {
		element = element || document.body;
		var clickToShows = element.querySelectorAll(".clicktoshow");
		for (var i = 0; i < clickToShows.length; i++) {
			SpecialEffects.setupClickToShowArea(clickToShows[i]);
		}
	};
}
