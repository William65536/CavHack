const fs = require('fs');
const path = require('path');

// 1970-01-01,27.183000000000003,0.247,Abidjan,Coste D'Ivoire,5.63N,3.23W

const cons = line => {
    if (line === '')
        return null;

    const temp = line.split(',');

    if (!temp[5])
        console.log(temp);

    const ret = {
        year: +temp[0]?.split('-')[0],
        temp: +temp[1],
        city: temp[3],
        lat: +temp[5].substring(0, temp[5].length - 1) * (temp[5][temp[5].length - 1] === 'N' ? 1 : -1),
        lng: +temp[6].substring(0, temp[6].length - 2) * (temp[6][temp[6].length - 2] === 'W' ? 1 : -1)
    };

    return ret;
};

fs.readFile(path.join(__dirname, 'GlobalLandTemperaturesByCity.csv'), { 'encoding': 'utf-8' }, (err, data) => {
    if (err)
        console.error(err);

    const arr = data.split('\n');

    const consarr = arr.map((_value, index) => cons(arr[index])).filter(value => value);

    fs.writeFile(path.join(__dirname, 'render\\minor.js'), JSON.stringify(consarr), { 'encoding': 'utf-8' }, err => {
        if (err)
            console.log(err);
    });
});