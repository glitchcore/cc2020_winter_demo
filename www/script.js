const DEMO_SAMPLE_RATE = 14400;

let kick_freq = 300;
let bass_freq = 50;

let freq = bass_freq;

let trance_time = 0;
const trance_period = 0.1 * DEMO_SAMPLE_RATE;

let kick_time = trance_period / 2;// trance_period;
const kick_period = trance_period * 4;

let freq_change_time = 0;
const freq_change_period = trance_period * 16;

let snare_time = -kick_period / 1.1;
const snare_period = kick_period * 2;

let lead_time = kick_period / 2;
let lead_period = kick_period / 3; 

let lead_multiplier = 2;

let noise = 0;

let phase = 0;

function render_sound(t) {
    let saw_a = 1000;
    let pwm_saw = (t / 100) % 1000;
    let pwm = 500; // 200 + (pwm_saw < 500 ? pwm_saw : (1000 - pwm_saw));

    pwm = pwm < 100 ? 100 : pwm;

    pwm = pwm > 900 ? 900 : pwm;

    if(t - trance_time > trance_period) {
        trance_time = t;
    }

    if(t - trance_time < 0.03 * DEMO_SAMPLE_RATE) {
        pwm = 0;
    }

    if(t - lead_period - lead_time > lead_period) {
        lead_time = t;
        lead_multiplier = 3.9; //Math.round(Math.random() * 5 + 1);
        lead_period = kick_period / 6;//  Math.round(Math.random() * 6 + 1);
    }

    /*
    // lead sound
    if(t - lead_time < lead_period / 4) {
        freq = bass_freq * lead_multiplier;
    }
    */

    if(t - kick_time > kick_period) {
        kick_time = t;

        freq = kick_freq;
    }

    if(t - freq_change_time > freq_change_period) {
        freq_change_time = t;

        // bass_freq = 50 + Math.random() * 30;

        /*
        if(bass_freq > 440 && false) {
            bass_freq = 120;
        }
        */

        kick_freq = bass_freq * 10;
    }

    if(t - snare_time > snare_period) {
        snare_time = t;
    }

    /* 
    // snare sound
    if(t - snare_time < 0.04 * DEMO_SAMPLE_RATE) {
        if(t % 5 == 0) {
            noise = Math.random() > 0.5 ? 1 : 0;
        }

        return noise;
    }
    */

    if(freq > bass_freq) {
        freq -= (kick_freq / 0.15) * (1 / DEMO_SAMPLE_RATE);
    } 

    phase += (1/DEMO_SAMPLE_RATE) * freq;

    if(freq > bass_freq) {
        pwm = 500;
    }

    let saw_wave = ((phase / 1.5) % 2) * 1000;

    let pulse_wave = saw_wave > pwm ? 1 : 0;

    return pulse_wave;
}

function play() {
    var context = new AudioContext();
    var node = context.createScriptProcessor(4096, 1, 1);

    let samples = 0;

    const sample_rate = context.sampleRate;

    console.log(sample_rate);

    node.onaudioprocess = function(audioProcessingEvent) {

        let outputBuffer = audioProcessingEvent.outputBuffer;

        for (var channel = 0; channel < outputBuffer.numberOfChannels; channel++) {
            var outputData = outputBuffer.getChannelData(channel);

            for (var sample = 0; sample < outputBuffer.length; sample++) {
                samples++;

                let t = Math.round(samples * DEMO_SAMPLE_RATE / sample_rate);

                let output = render_sound(t);

                // console.log(output);

                // outputData[sample] =  Math.sin(t * 440 * 6.28 / DEMO_SAMPLE_RATE); // output * 2 - 1;

                outputData[sample] =  output * 2 - 1;
            }
        }
    }

    node.connect(context.destination);
}
