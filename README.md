# Unofficial Steam DRM (SDRM)
Unofficial steam drm for node.js desktop apps


## 📢 Notice
This is a small protection for your app. And this does not protect your app 100%.

As you know, there are people who developing a software, that can remove steam drm layer from .exe file.

Just like how that is possible, this method cannot secure your app 100%. And there are always people who want to break your software.

So in general, i recommend developers to hire a law firm, for taking care of any problem that can be done within law.

However drm is still a good protection. And it is always better than nothing.


## ▶️ install
```
npm i sdrm
```

## 🛠 Build
```
node-gyp build
```

or

```
node-gyp rebuild
```

## ⚔ Requirement
### Module requirement
| Prop | Requirement | 
| - | - |
| Node.js | It has not been tested. But i believe it would work with version 12+. However a published package is built with Node.js version 16+. |
| OS | Windows 10+. A published package is built and tested in Windows 10. Please try build a sdrm module yourself for other OS. You can try publishing a sdrm module with the name like "sdrm-mac", "sdrm-linux" so other people can find it. |
| .dll file | steam_api64.dll from steam sdk. It does not come withe the npm package. |

### Build requirement
| Prop | Requirement | 
| - | - |
| Build tool | node-gyp and anything that is needed for building NAPI |


## 📖 Example
This example will be the case where filename is just name of dll file eg."steam_api64.dll"

For development, steam_api64.dll can be placed next to package.json.

For production, place steam_api64.dll next to .exe file.

### In general:
```
// it will throw error if it fails.
// or it may return boolean true/false
try
{
    // SDRM(filename;file path as a string, app id number)
    SDRM("steam_api64.dll", 00000000);
    // it will throw error if it fails.
}
catch(e)
{
    console.log(e);
}
```

### Electron.js:
```
app.on('ready',()=>{
    try
    {
        // SDRM(filename;file path as a string, app id number)
        SDRM("steam_api64.dll", 00000000);
        // it will throw error if it fails.
        createWindow();
    }
    catch(e)
    {
        console.log(e);
        if (process.platform !== 'darwin') app.quit();
        // or just app.quit() without if statement.
    }
});
```


## 👨‍💻 Author
[Victor Chanil Park](https://github.com/opdev1004)


## 💯 License
MIT, See [LICENSE](./LICENSE).