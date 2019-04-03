package main

import (
	"net/http"

	"github.com/gin-gonic/gin"
)

func main() {
	gin.SetMode(gin.DebugMode)
	db := make(map[string]string)
	db["shibin"] = "haha"

	router := gin.Default()
	router.GET("/ping", func(ctx *gin.Context) {
		ctx.JSON(http.StatusOK, gin.H{
			"message": "pong",
		})
	})

	router.GET("/user/search", func(ctx *gin.Context) {
		ctx.DefaultQuery("hhh", "shanghai")
	})

	router.GET("/user/:name", func(ctx *gin.Context) {
		name := ctx.Params.ByName("name")
		if val, ok := db[name]; ok {
			ctx.JSON(http.StatusOK, gin.H{
				"name":  name,
				"value": val,
			})
		} else {
			ctx.JSON(http.StatusOK, gin.H{
				"name":   name,
				"status": "no found",
			})
		}
	})

	router.Run() // listen and serve on 0.0.0.0:8080
}
