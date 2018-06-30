
//var codepoints_db = {}
//var icon_db = {}
//console.log("icon_db: "+icon_db)
function convertStringToUnicode(text){
    var str = "\\u" + text
    var jsonstr = '{"ustr":"'+str+'"}'
//    console.log("jsonstr: "+jsonstr)
    var obj = JSON.parse(jsonstr)
    return obj.ustr
}

function convertNameToText(name, nameMap){
    console.log("name: "+name+" nameMap"+nameMap)
    if(name!==null && name!==""){
        var text = nameMap[name]
        if(text === null || text === undefined){
            console.log("convert fail: " + name)
        }else{
            console.log("convert success: "+ text)
        }
        return convertStringToUnicode(text)
    }
    return ""
}

function readFile(url, onLoad, onProgress, onError) {
    var request = new XMLHttpRequest();

    request.onreadystatechange = function() {
        if (request.readyState === XMLHttpRequest.DONE) {
            // TODO: Re-visit https://bugreports.qt.io/browse/QTBUG-45581 is solved in Qt
            if (request.status == 200 || request.status == 0) {
                var res = request.responseText
                codepoints_db[url] = res
                console.time('Process file: "' + url + '"');
                onLoad( res );
                console.timeEnd('Process file: "' + url + '"');

            }
            else if ( onError !== undefined ) {
                onError();
            }
        }
        else if (request.readyState === XMLHttpRequest.HEADERS_RECEIVED) {
            if ( onProgress !== undefined ) {
                onProgress();
            }
        }
    };

    request.open( 'GET', url, true );
    request.send( null );
}

function generateNameMap(res){
    var arr = res.split('\n')
    var nameMap = {}
    for(var i = 0; i<arr.length;i++){
        var item = arr[i].split(' ')
        nameMap[item[0]] = item[1]
    }
    return nameMap
}


