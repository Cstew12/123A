

import React from 'react';
import { NavigationContainer } from '@react-navigation/native';
import { createNativeStackNavigator } from '@react-navigation/native-stack';
import LoginScreen from './app/screens/LoginScreen';
//import { SafeAreaProvider } from 'react-native-safe-area-context';
const Stack = createNativeStackNavigator();
export default function App() {
  
  return (
    //<SafeAreaProvider>
      <NavigationContainer>
        <Stack.Navigator initialRouteName={LoginScreen}>
          {/* Order of the stack screens please don't change the order */}
          <Stack.Screen name="Login" options={{headerShown: false}} component={LoginScreen} />
        </Stack.Navigator>
      </NavigationContainer>
    //</SafeAreaProvider>
  );
}
