// start.js



Page({



  /**

   * 页面的初始数据

   */

  

  getDataFromOneNet: function () {

    //从oneNET请求我们的智能垃圾桶的数据

    const requestTask = wx.request({

      url: 'https://api.heclouds.com/devices/503154232/datapoints?datastream_id=Distance&limit=15',

      header: {

        'content-type': 'application/json',

        'api-key': 'Runw5tlO0zk4IZxZ8bb1z648Szg='

      },

      success: function (res) {

        //console.log(res.data)

        //拿到数据后保存到全局数据

        var app = getApp()

        app.globalData.temperature = res.data.data.datastreams[0]

        console.log(app.globalData)

        wx.navigateTo({

          url: '../my_height/my_height',

        })

      },



      fail: function (res) {

        console.log("fail!!!")

      },



      complete: function (res) {

        console.log("end")

      }

    })

  },



  change: function (e) {

    //当有输入时激活发送按钮，无输入则禁用按钮

    if (e.detail.value != "") {

      this.setData({

        threshold: e.detail.value,

        opacity: 1,

        disabled: false,

      })

    } else {

      this.setData({

        threshold: 0,

        opacity: 0.4,

        disabled: true,

      })

    }

  },



  /**

   * 生命周期函数--监听页面加载

   */

  onLoad: function (options) {



  },



  /**

   * 生命周期函数--监听页面初次渲染完成

   */

  onReady: function () {



  },



  /**

   * 生命周期函数--监听页面显示

   */

  onShow: function () {



  },



  /**

   * 生命周期函数--监听页面隐藏

   */

  onHide: function () {



  },



  /**

   * 生命周期函数--监听页面卸载

   */

  onUnload: function () {



  },



  /**

   * 页面相关事件处理函数--监听用户下拉动作

   */

  onPullDownRefresh: function () {



  },



  /**

   * 页面上拉触底事件的处理函数

   */

  onReachBottom: function () {



  },



  /**

   * 用户点击右上角分享

   */

  onShareAppMessage: function () {



  }

})