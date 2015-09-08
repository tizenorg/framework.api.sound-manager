Name:       capi-media-sound-manager
Summary:    Sound Manager library
Version:    0.2.27
Release:    0
Group:      libdevel
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:  cmake
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(mm-sound)
BuildRequires:  pkgconfig(mm-session)
BuildRequires:  pkgconfig(capi-base-common)
BuildRequires:  pkgconfig(vconf)
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig
Requires(post): libprivilege-control

%description
A Sound Manager library in Tizen C API

%package devel
Summary:  Sound Manager library (Development)
Group:    TO_BE/FILLED_IN
Requires: %{name} = %{version}-%{release}

%description devel
A Sound Manager library in Tizen C API (DEV)

%prep
%setup -q


%build
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
cmake . -DCMAKE_INSTALL_PREFIX=/usr -DFULLVER=%{version} -DMAJORVER=${MAJORVER}


make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
mkdir -p %{buildroot}/usr/share/license
mkdir -p %{buildroot}/opt/usr/devel
cp LICENSE %{buildroot}/usr/share/license/%{name}
cp test/sound_manager_test %{buildroot}/opt/usr/devel

%make_install

%post
/sbin/ldconfig
/usr/bin/api_feature_loader --verbose --dir=/usr/share/privilege-control

%postun -p /sbin/ldconfig


%files
%{_libdir}/libcapi-media-sound-manager.so.*
%{_datadir}/license/%{name}
/opt/usr/devel/*
%manifest capi-media-sound-manager.manifest

%files devel
%{_includedir}/media/sound_manager.h
%{_includedir}/media/sound_manager_internal.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/libcapi-media-sound-manager.so


