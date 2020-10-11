const osuReplayParser = require('osureplayparser');
const utils = require('./node_modules/osureplayparser/utils/utils.js');

const replayPath = 'C:/Users/Danila/Desktop/rawrpdata/fast.osr';
const replay = osuReplayParser.parseReplay(replayPath);

var replayDonee = replay.replace(/\|/g , "\n");
var replayDoneee = replayDonee.replace(/,/g , "\n");

console.log(replay);

//Generally the module name and the variable name both are same
var fs = require('fs');

// this line of code creates an another file output.txt and writes the data in sample into the log.
fs.writeFileSync('output.txt',replayDoneee);