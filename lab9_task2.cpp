#include <unordered_map>
#include <string>
#include <iostream>
#include <memory>
using namespace std;

// Existing PayPal class (no changes needed)
class PayPal
{
public:
    void makePayment(std::string item)
    {
        std::cout << "Making PayPal payment for item: " << item << std::endl;
    }

    bool verifyPayment(std::string transactionId)
    {
        std::cout << "Verifying PayPal payment with transaction ID: " << transactionId << std::endl;
        return true;
    }

    void refundPayment(std::string item)
    {
        std::cout << "Refunding PayPal payment for item: " << item << std::endl;
    }
};

// Existing Stripe class (no changes needed)
class Stripe
{
public:
    void chargePayment(std::string item)
    {
        std::cout << "Charging Stripe payment for item: " << item << std::endl;
    }

    bool verifyCharge(std::string transactionId)
    {
        std::cout << "Verifying Stripe payment with transaction ID: " << transactionId << std::endl;
        return true;
    }

    void issueRefund(std::string item)
    {
        std::cout << "Issuing Refund for Stripe payment for item: " << item << std::endl;
    }
};

// Uniform Payment Provider Interface
class PaymentProvider
{
public:
    virtual ~PaymentProvider() = default;
    virtual void processPayment(std::string paymentInfo) = 0;
    virtual void refundPayment(std::string refundInfo) = 0;
    virtual bool verifyPayment(std::string paymentInfo) = 0;
};

// PayPal Adapter
class PayPalAdapter : public PaymentProvider
{
private:
    PayPal paypal;

public:
    void processPayment(std::string paymentInfo) override
    {
        paypal.makePayment(paymentInfo);
    }

    void refundPayment(std::string refundInfo) override
    {
        paypal.refundPayment(refundInfo);
    }

    bool verifyPayment(std::string paymentInfo) override
    {
        return paypal.verifyPayment(paymentInfo);
    }
};

// Stripe Adapter
class StripeAdapter : public PaymentProvider
{
private:
    Stripe stripe;

public:
    void processPayment(std::string paymentInfo) override
    {
        stripe.chargePayment(paymentInfo);
    }

    void refundPayment(std::string refundInfo) override
    {
        stripe.issueRefund(refundInfo);
    }

    bool verifyPayment(std::string paymentInfo) override
    {
        return stripe.verifyCharge(paymentInfo);
    }
};

// Payment Gateway
class PaymentGateWay
{
private:
    std::unordered_map<std::string, std::unique_ptr<PaymentProvider>> paymentProviders;

public:
    PaymentGateWay()
    {
        // Initialize with default providers
        paymentProviders["paypal"] = std::make_unique<PayPalAdapter>();
        paymentProviders["stripe"] = std::make_unique<StripeAdapter>();
    }

    void addPaymentProvider(std::string providerName, std::unique_ptr<PaymentProvider> paymentProvider)
    {
        paymentProviders[providerName] = std::move(paymentProvider);
    }

    void processPayment(std::string providerName, std::string paymentInfo)
    {
        if (paymentProviders.find(providerName) != paymentProviders.end())
        {
            paymentProviders[providerName]->processPayment(paymentInfo);
        }
        else
        {
            std::cout << "Payment provider not found: " << providerName << std::endl;
        }
    }

    void refundPayment(std::string providerName, std::string refundInfo)
    {
        if (paymentProviders.find(providerName) != paymentProviders.end())
        {
            paymentProviders[providerName]->refundPayment(refundInfo);
        }
        else
        {
            std::cout << "Payment provider not found: " << providerName << std::endl;
        }
    }

    bool verifyPayment(std::string providerName, std::string paymentInfo)
    {
        if (paymentProviders.find(providerName) != paymentProviders.end())
        {
            return paymentProviders[providerName]->verifyPayment(paymentInfo);
        }
        else
        {
            std::cout << "Payment provider not found: " << providerName << std::endl;
            return false;
        }
    }
};

// Example usage
int main()
{
    PaymentGateWay gateway;

    // Process payments using different providers
    gateway.processPayment("paypal", "Item1");
    gateway.processPayment("stripe", "Item2");

    // Verify payments
    gateway.verifyPayment("paypal", "TXN123");
    gateway.verifyPayment("stripe", "TXN456");

    // Refund payments
    gateway.refundPayment("paypal", "Item1");
    gateway.refundPayment("stripe", "Item2");

    return 0;
}
