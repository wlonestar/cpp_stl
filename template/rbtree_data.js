const tree = {
  "timestamp": "2023-08-06_21-51-24.133",
  "n": 20,
  "nodes": [
    {
      "value": 26,
      "color": "black",
      "parent": "null",
      "left": "17",
      "right": "28",
      "key": 26
    },
    {
      "value": 17,
      "color": "black",
      "parent": "26",
      "left": "8",
      "right": "20",
      "key": 17
    },
    {
      "value": 28,
      "color": "black",
      "parent": "26",
      "left": "27",
      "right": "38",
      "key": 28
    },
    {
      "value": 8,
      "color": "red",
      "parent": "17",
      "left": "3",
      "right": "15",
      "key": 8
    },
    {
      "value": 20,
      "color": "red",
      "parent": "17",
      "left": "18",
      "right": "22",
      "key": 20
    },
    {
      "value": 27,
      "color": "black",
      "parent": "28",
      "left": "null",
      "right": "null",
      "key": 27
    },
    {
      "value": 38,
      "color": "red",
      "parent": "28",
      "left": "36",
      "right": "39",
      "key": 38
    },
    {
      "value": 3,
      "color": "black",
      "parent": "8",
      "left": "null",
      "right": "null",
      "key": 3
    },
    {
      "value": 15,
      "color": "black",
      "parent": "8",
      "left": "12",
      "right": "16",
      "key": 15
    },
    {
      "value": 18,
      "color": "black",
      "parent": "20",
      "left": "null",
      "right": "19",
      "key": 18
    },
    {
      "value": 22,
      "color": "black",
      "parent": "20",
      "left": "21",
      "right": "24",
      "key": 22
    },
    {
      "value": 36,
      "color": "black",
      "parent": "38",
      "left": "34",
      "right": "37",
      "key": 36
    },
    {
      "value": 39,
      "color": "black",
      "parent": "38",
      "left": "null",
      "right": "null",
      "key": 39
    },
    {
      "value": 12,
      "color": "red",
      "parent": "15",
      "left": "null",
      "right": "null",
      "key": 12
    },
    {
      "value": 16,
      "color": "red",
      "parent": "15",
      "left": "null",
      "right": "null",
      "key": 16
    },
    {
      "value": 19,
      "color": "red",
      "parent": "18",
      "left": "null",
      "right": "null",
      "key": 19
    },
    {
      "value": 21,
      "color": "red",
      "parent": "22",
      "left": "null",
      "right": "null",
      "key": 21
    },
    {
      "value": 24,
      "color": "red",
      "parent": "22",
      "left": "null",
      "right": "null",
      "key": 24
    },
    {
      "value": 34,
      "color": "red",
      "parent": "36",
      "left": "null",
      "right": "null",
      "key": 34
    },
    {
      "value": 37,
      "color": "red",
      "parent": "36",
      "left": "null",
      "right": "null",
      "key": 37
    }
  ],
  "links": [
    {
      "from": 26,
      "to": 17
    },
    {
      "from": 26,
      "to": 28
    },
    {
      "from": 26,
      "to": 17
    },
    {
      "from": 17,
      "to": 8
    },
    {
      "from": 17,
      "to": 20
    },
    {
      "from": 26,
      "to": 28
    },
    {
      "from": 28,
      "to": 27
    },
    {
      "from": 28,
      "to": 38
    },
    {
      "from": 17,
      "to": 8
    },
    {
      "from": 8,
      "to": 3
    },
    {
      "from": 8,
      "to": 15
    },
    {
      "from": 17,
      "to": 20
    },
    {
      "from": 20,
      "to": 18
    },
    {
      "from": 20,
      "to": 22
    },
    {
      "from": 28,
      "to": 27
    },
    {
      "from": 28,
      "to": 38
    },
    {
      "from": 38,
      "to": 36
    },
    {
      "from": 38,
      "to": 39
    },
    {
      "from": 8,
      "to": 3
    },
    {
      "from": 8,
      "to": 15
    },
    {
      "from": 15,
      "to": 12
    },
    {
      "from": 15,
      "to": 16
    },
    {
      "from": 20,
      "to": 18
    },
    {
      "from": 18,
      "to": 19
    },
    {
      "from": 20,
      "to": 22
    },
    {
      "from": 22,
      "to": 21
    },
    {
      "from": 22,
      "to": 24
    },
    {
      "from": 38,
      "to": 36
    },
    {
      "from": 36,
      "to": 34
    },
    {
      "from": 36,
      "to": 37
    },
    {
      "from": 38,
      "to": 39
    },
    {
      "from": 15,
      "to": 12
    },
    {
      "from": 15,
      "to": 16
    },
    {
      "from": 18,
      "to": 19
    },
    {
      "from": 22,
      "to": 21
    },
    {
      "from": 22,
      "to": 24
    },
    {
      "from": 36,
      "to": 34
    },
    {
      "from": 36,
      "to": 37
    }
  ]
}

const nodeDataArray = tree.nodes
const linkDataArray = tree.links
