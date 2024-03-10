#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CURRENCIES 10 // Máximo número de monedas soportadas

typedef struct {
    char name[50];
    char code[10];
    float exchangeRate;
} Currency;

typedef struct {
    Currency* listOfCurrencies;
    int numberOfCurrencies;
} CurrencyConverter;

void addCurrency(CurrencyConverter* converter, Currency newCurrency) {
    if (converter->numberOfCurrencies >= MAX_CURRENCIES) {
        printf("Maximum number of currencies reached.\n");
        return;
    }
    converter->listOfCurrencies[converter->numberOfCurrencies] = newCurrency;
    converter->numberOfCurrencies++;
}

int findCurrency(CurrencyConverter* converter, char* code) {
    for (int i = 0; i < converter->numberOfCurrencies; i++) {
        if (strcmp(converter->listOfCurrencies[i].code, code) == 0) {
            return i;
        }
    }
    return -1;
}

float convert(CurrencyConverter* converter, char* sourceCode, char* destinationCode, float amount) {
    int sourceIndex = findCurrency(converter, sourceCode);
    int destinationIndex = findCurrency(converter, destinationCode);
    
    if (sourceIndex == -1 || destinationIndex == -1) {
        printf("Currency not found.\n");
        return -1;
    }
    
    return amount * converter->listOfCurrencies[destinationIndex].exchangeRate / converter->listOfCurrencies[sourceIndex].exchangeRate;
}

int main() {
    CurrencyConverter converter;
    converter.listOfCurrencies = (Currency*)malloc(MAX_CURRENCIES * sizeof(Currency));
    converter.numberOfCurrencies = 0;
    
    // Agregar las monedas disponibles
    addCurrency(&converter, (Currency){"Dólar estadounidense", "USD", 1.0});
    addCurrency(&converter, (Currency){"Euro", "EUR", 0.91});
    addCurrency(&converter, (Currency){"Quetzal", "Q", 7.81});
    addCurrency(&converter, (Currency){"Peso mexicano", "MXN", 16.80});
    
    // Solicitar datos al usuario
    char sourceCode[10], destinationCode[10], currenciesCode[100];
    float amount;

    
    for (int i = 0; i < converter.numberOfCurrencies; i++) {
        if(i > 0){
            strcat(currenciesCode, ", ");
        }
        strcat(currenciesCode, converter.listOfCurrencies[i].code);
    }
    printf("Ingrese la moneda de origen (%s): ", currenciesCode);
    scanf("%s", sourceCode);
    printf("Ingrese la moneda de destino (%s): ", currenciesCode);
    scanf("%s", destinationCode);
    printf("Ingrese la cantidad a convertir: ");
    scanf("%f", &amount);
    
    // Convertir la cantidad
    float convertedAmount = convert(&converter, sourceCode, destinationCode, amount);
    
    // Mostrar el resultado
    if (convertedAmount != -1) {
        printf("%.2f %s es equivalente a %.2f %s\n", amount, sourceCode, convertedAmount, destinationCode);
    }
    
    free(converter.listOfCurrencies); // Liberar la memoria asignada dinámicamente
    return 0;
}
