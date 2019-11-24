let site = {
    relays: [],
    init: () => {
        site.getInfo()
        site.getRelays()
        site.setupElements()
        site.setupScheduleForm()
        site.syncClock()
    },
    syncClock: () => {
        let sync = document.getElementById("sync-clock")
        sync.addEventListener("submit", (e) => {
            e.preventDefault()
            let datetime = new Date()
            let data = {
                hour: datetime.getHours(),
                minute: datetime.getMinutes(),
                second: datetime.getSeconds(),
                day: datetime.getDay(),
                month: datetime.getMonth(),
                year: datetime.getFullYear()
            }
            xhttp = new XMLHttpRequest()
            xhttp.open("post", sync.action, true)
            xhttp.setRequestHeader("Content-type", "application/json")
            xhttp.send(JSON.stringify(data))
        })
    },
    setupScheduleForm: () => {
        let form = document.getElementById("scheduling")
        form.addEventListener("submit", (e) => {
            e.preventDefault()
            xhttp = new XMLHttpRequest()
            xhttp.open("post", form.action, true)
            xhttp.setRequestHeader("Content-type", "application/json")
            let ontime = document.getElementById("ontime").value.split(':')
            let offtime = document.getElementById("offtime").value.split(':')
            let data = {
                ontime: {
                    hour: Number(ontime[0]),
                    minute: Number(ontime[1])
                },
                offtime: {
                    hour: Number(offtime[0]),
                    minute: Number(offtime[1])
                }
            }
            xhttp.send(JSON.stringify(data))
        })
    },
    getRelays: () => {
        xhttp = new XMLHttpRequest()
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                site.relays = JSON.parse(this.responseText)
                site.setupElements()
            }
        }
        xhttp.open("get", "/relays.json", true)
        xhttp.send()
    },
    getInfo: () => {
        xhttp = new XMLHttpRequest()
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                let data = JSON.parse(this.responseText)
                if (data.datetime > 100000000) {
                    document.getElementById("sync-clock").hidden = true
                }
                if (data.ontime != "00:00:00") {
                    document.getElementById("ontime").value = data.ontime
                }
                if (data.offtime != "00:00:00") {
                    document.getElementById("offtime").value = data.offtime
                }
            }
        }
        xhttp.open("get", "/info.json", true)
        xhttp.send()

    },
    setupElements: () => {
        let body = document.getElementById('switches')
        while (body.firstChild) {
            body.removeChild(body.firstChild)
        }
        site.relays.forEach(relay => {
            let container = document.createElement('tr')
            let td0 = document.createElement('td')
            let td1 = document.createElement('td')
            let td2 = document.createElement('td')
            let action = document.createElement('button')
            td1.textContent = '●'
            td1.classList.add(relay.state == 1 ? 'active' : 'inactive')
            action.textContent = 'Toggle'
            td0.textContent = "Light " + relay.gpio
            td2.append(action)
            action.addEventListener("click", (e) => {
                xhttp = new XMLHttpRequest()
                xhttp.open("POST", "/relay", true)
                xhttp.setRequestHeader("Content-type", "application/json")
                let data = {
                    gpio: relay.gpio,
                    state: (relay.state ? 0 : 1),
                }
                xhttp.send(JSON.stringify(data))
                site.getRelays()
            })
            container.append(td0)
            container.append(td1)
            container.append(td2)
            body.append(container)
        })
    }
}
site.init()