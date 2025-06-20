// Decode the credentials by using the `decoder` function.

// Hint: Look closely, it's more than just characters. 
const correctUser = [97, 100, 109, 105, 110];  
const correctPass = [108, 97, 109, 97, 114, 118, 56, 108, 111, 117, 115];  

function decoder(creds) {
    let credentials = '';
    for (let i = 0; i < creds.length; i++) {
        credentials += String.fromCharCode(creds[i]);
    }
    return credentials;
}

console.log("Username:" + decoder(correctUser)); 

console.log("Password: " + decoder(correctPass));  



