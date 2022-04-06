import React, { useState, useEffect } from "react";
import { StyleSheet, Text,View, Pressable, Image, TextInput} from "react-native";
import { Button, Input } from "react-native-elements";
import { useNavigation } from "@react-navigation/core";

const LoginScreen = () => {
    const navigation = useNavigation();
  
  
    // UI Split up into 3 main flexes: Header (for logo and title),
    // Login (for input fields and login button),
    // and SignUp (for Sign up button)
  
    return (
      <View style={styles.container}>
        <View style={styles.headerFlex}>
          <Image
            source={require("./../../Assets/SocialDistanceLogo.jpeg")}
            style={styles.image1}
          />
  
          <Text style={styles.titleText}>Social Distancers</Text>
  
          <Text style={styles.quoteText}>Keeping the World Safe!</Text>
        </View>
          
  
      </View>
    );
  };
  
  // Component styles
  const styles = StyleSheet.create({
    container: {
      flex: 1,
      backgroundColor: "#2e2d2d",
      alignItems: "center",
      justifyContent: "center",
    },
    item: {
      backgroundColor: "#f9c2ff",
      padding: 20,
      marginVertical: 8,
      marginHorizontal: 16,
    },
    title: {
      fontSize: 32,
    },
    headerFlex: {
      flex: 3.4,
      backgroundColor: "#2e2d2d",
      justifyContent: "flex-end",
      alignItems: "center",
    },
  
    loginFlex: {
      flex: 3,
      backgroundColor: "#2e2d2d",
      justifyContent: "center",
    },
  
    signupFlex: {
      flex: 1,
      backgroundColor: "#2e2d2d",
      justifyContent: "flex-start",
    },
  
    smallText: {
      fontSize: 12,
      color: "#9c9c9c",
      fontFamily: "Al Nile",
      marginLeft: 0,
    },
  
    titleText: {
      fontSize: 50,
      color: "#82f591",
      fontFamily: "AvenirNext-Bold",
      marginBottom: -10,
    },
  
    quoteText: {
      fontSize: 12,
      color: "#9c9c9c",
      fontFamily: "AvenirNext-Bold",
      marginTop: 5,
    },
  
    image1: {
      width: 160,
      height: 250,
      marginBottom: -20,
      marginLeft: -22,
    },
  });
  
  export default LoginScreen;