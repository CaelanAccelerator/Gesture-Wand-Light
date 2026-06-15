#pragma once

#include "ILight.hpp"
#include "Gesture.hpp"
#include "Palette.hpp"
#include "Animator.hpp"

enum class AnimMode {
    None,
    // Breathing, Flow, Heartbeat...  future version
};

struct LightState {
	LightState(){
		printf("LightState constructed \r\n");
		printf("state.brightness is %d \r\n", brightness);
	}
	static constexpr int BRIGHTNESS_CHANGE = 20;
	static constexpr int NUM_COLORS = 4;
	AnimMode mode = AnimMode::None;
    uint8_t brightness = 255;
    uint8_t isOn = 0;
    uint8_t curColor = 0;// default color
    Palette const colors[NUM_COLORS] = {Palettes::Sunset, Palettes::Lighting, Palettes::PinkBlue, Palettes::Aurora};
};

class LightController{
public:
	LightController(Animator *animator) : animator_(animator) {
		animator_->setBrightness(state.brightness * state.isOn);
		animator_->renderPalette(state.colors[state.curColor % state.NUM_COLORS]);
		animator_->show();
	}

	Status handleGesture(Gesture g){
		switch (g){
		case Gesture::None:
			break;
		case Gesture::SwingUp:
			state.brightness = state.brightness + state.BRIGHTNESS_CHANGE > 255 ? 255 : state.brightness + state.BRIGHTNESS_CHANGE;
			break;
		case Gesture::SwingDown:
			state.brightness = state.brightness - state.BRIGHTNESS_CHANGE < 0 ? 0 : state.brightness - state.BRIGHTNESS_CHANGE;
			break;
		case Gesture::SwingSide:
			state.curColor += 1;
			break;
		case Gesture::Circle:
			if(state.isOn)
				state.isOn = 0;
			else
				state.isOn = 1;
			break;
		}

		return render();
	}

private:
	Status render(){
		Status res1 = animator_->renderPalette(state.colors[state.curColor % state.NUM_COLORS]);
		if(res1 == Status::Err){
			printf("fail to render palette\r\n");
			return Status::Err;
		}
		Status res2 = animator_->setBrightness(state.brightness * state.isOn);
		if(res2 == Status::Err){
			printf("fail to set brightness\r\n");
			return Status::Err;
		}
		Status res3 = animator_->show();
		if(res3 == Status::Err){
			printf("fail to flush state\r\n");
			return Status::Err;
		}

		return Status::OK;
	}
	Animator *animator_;
	LightState state;
};
