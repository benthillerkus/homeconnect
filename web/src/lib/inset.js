!(function () {
  "use strict"
  void 0 === CanvasRenderingContext2D.prototype.shadowInset &&
    (function () {
      function t(t) {
        var a = void 0
        return n.has(t) ? (a = n.get(t)) : ((a = document.createElement("canvas")), n.set(t, a)), a
      }
      function a(t, a) {
        var e = h[t]
        h[t] = function () {
          this.shadowInset === !0 ? a(this, e, arguments) : e.apply(this, arguments)
        }
      }
      function e(t, a, e) {
        var i = a.width + 2 * e,
          n = a.height + 2 * e
        ;(t.width !== i || t.height !== n) &&
          (t.width !== i && (t.width = i),
          t.height !== n && (t.height = n),
          t.getContext("2d").translate(e, e))
      }
      function i(t, a) {
        ;["shadowBlur", "shadowOffsetX", "shadowOffsetY", "shadowColor"].forEach(function (e) {
          var i = t[e]
          ;(t[e] = a[e]), (a[e] = i)
        })
      }
      var n = new WeakMap(),
        h = CanvasRenderingContext2D.prototype,
        o = h.fillRect,
        r = h.drawImage,
        c = ["fill", "fillRect", "drawImage"],
        d = [
          "beginPath",
          "closePath",
          "moveTo",
          "lineTo",
          "bezierCurveTo",
          "quadraticCurveTo",
          "arc",
          "arcTo",
          "rect"
        ]
      ;(h.shadowInset = !1),
        d.forEach(function (i) {
          a(i, function (a, i, n) {
            var h = a.canvas,
              o = t(h),
              r = o.getContext("2d")
            e(o, h, Math.max(h.width, h.height)), i.apply(r, n), i.apply(a, n)
          })
        }),
        c.forEach(function (n) {
          a(n, function (a, n, h) {
            var c = a.canvas,
              d = t(c),
              l = d.getContext("2d"),
              s = Math.max(c.width, c.height)
            e(d, c, s),
              n.apply(l, h),
              (l.globalCompositeOperation = "xor"),
              (l.fillStyle = "black"),
              o.apply(l, [-s, -s, d.width, d.height]),
              i(l, a),
              r.apply(l, [d, -s, -s]),
              n.apply(a, h),
              r.apply(a, [d, s, s, c.width, c.height, 0, 0, c.width, c.height]),
              l.clearRect(-s, -s, d.width, d.height),
              i(l, a)
          })
        })
    })()
})()
